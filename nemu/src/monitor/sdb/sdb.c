/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <utils.h>
#include "sdb.h"
#include <memory/host.h>
word_t expr(char *e, bool *success);
word_t warp_pmem_read(paddr_t addr) ;

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  nemu_state.state=NEMU_QUIT;
  return -1;
}
//my_func start!
static int cmd_step(char *args){
  int time=1;
  if(args)
    sscanf(args,"%d",&time);
  cpu_exec(time);
  // printf("cmd_step :%d",time);
  return 0;
}
static int cmd_print_status(char *args){
  char op;
  if(!args){
    printf("Please enter a operation(w/r)!");
    return 0;
  }
  sscanf(args,"%c",&op);
  switch(op){
    case 'r':
      isa_reg_display();
    break;
    case 'w':
      printf("Watch Point not imped");
    break;
    default:
    printf("Please enter a operation(w/r)!");
    return 0;
  }
  // printf("cmd_print_status :%s",args);
  return 0;
}
static int cmd_scan_mem(char *args){
  int n;
  paddr_t addr;
  sscanf(args,"%d %x",&n,&addr);
  for(;n>0;n--){
    //这个似乎有问题！！
    // 进制问题（^-^）
    // printf("readMem %lu %lu %lu %lu" ,warp_pmem_read(addr,1),warp_pmem_read(addr+1,1),warp_pmem_read(addr+2,1),warp_pmem_read(addr+3,1));
    printf("<0x%010x>    0x%08lx\n",addr,warp_pmem_read(addr));
    addr+=4;
  }
  // printf("cmd_scan_mem :%s",args);
  return 0;
}
static int cmd_eval(char *args){
  {  FILE* fp=fopen("/home/seeker/Develop/ysyx-workbench/nemu/tools/gen-expr/build/input","r");
int result;
char* exp=malloc(700*sizeof(char));
while(fscanf(fp,"%d %s",&result,exp)){
  bool ok=true;
  int res=expr(exp,&ok);
  if(ok&&result!=res)
    printf("fail!  %s\n",exp);
  else
    printf("OK");
}}
  bool success;
  word_t result=expr(args,&success);

  if (success){
    printf("cmd_eval :%s, result=%lu\n",args,result);
  }else{
    printf("Error");

  }
  return 0;
}
static int cmd_watch(char *args){
  printf("cmd_watch :%s",args);
  return 0;
}
static int cmd_del_watch(char *args){
  printf("cmd_del_watch :%s",args);
  return 0;
}
//my_func end!

static int cmd_help(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "Single-step execution", cmd_step },
  { "info", "Print the status of the program.(reg,watchpoint..etc)", cmd_print_status },
  { "x", "Scan mem", cmd_scan_mem },
  { "p", "Eval expression", cmd_eval },
  { "w", "Set WatchPoint", cmd_watch },
  { "d", "Delete WatchPoint", cmd_del_watch },
  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
