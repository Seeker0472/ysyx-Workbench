#include "am.h"
#include <proc.h>

#define MAX_NR_PROC 4

static PCB pcb[MAX_NR_PROC] __attribute__((used)) = {};
static PCB pcb_boot = {};
PCB *current = NULL;

void switch_boot_pcb() {
  current = &pcb_boot;

}

void hello_fun(void *arg) {
  int j = 1;
  while (1) {
    Log("Hello World from Nanos-lite with arg '%s' for the %dth time!", (char *)arg, j);
    j ++;
    yield();
  }
}
void context_uload(PCB *pcb, const char *filename, char *const argv[], char *const envp[]);
void context_kload(PCB *pcb, void *func,void*args);
void naive_uload(PCB *pcb, const char *filename);
void init_proc() {
  char *empty[] =  {"Test1","Test2",NULL };

  Log("Initializing processes...");
  // naive_uload(NULL, "/bin/float");
  // "/share/games/nes/mario.nes"
  // context_kload(&pcb[0], hello_fun, "aaa");
  // context_kload(&pcb[1], hello_fun, "BBB");
  // context_uload(&pcb[1], "/bin/env", empty, empty); // sig-fault!!
  context_uload(&pcb[1], "/bin/env",empty,empty);//sig-fault!!
  switch_boot_pcb();
  Log("GO!");
  // context_uload(&pcb[2], "/bin/pal");
  yield();
  assert(0);
  // load program here
}

Context *schedule(Context *prev) {
  Log("SHEDULE");
  int robin = 0;
  bool find=false;
  // find context,start robin
  current->cp=prev;
  if (current != &pcb_boot) {
    robin=current-pcb;
  }
  for (int i = (robin+1)%MAX_NR_PROC; true; i = (i + 1)%MAX_NR_PROC) {
    if (pcb[i].cp != NULL) {
      robin = i;
      current=&pcb[i];
      find=true;
      break;
    }
    // if(i==robin)
    
  }
  Log("goto:%d",robin);
  if (!find) {
    Log("INFO:NoThread Found,return TO Main");
    switch_boot_pcb(); 
    // current=&pcb_boot;
    return pcb_boot.cp;
  }
    // return prev;
  return pcb[robin].cp;
}
