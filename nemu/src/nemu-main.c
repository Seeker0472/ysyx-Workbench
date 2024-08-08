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

#include <common.h>
// #define TEST_CALC

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();
word_t expr(char *e, bool *success) ;
int main(int argc, char *argv[]) {
  /* Initialize the monitor. */

#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif
#ifdef TEST_CALC
  FILE *fp = fopen("/ysyx-workbench/nemu/tools/gen-expr/build/input", "r");
  int result;
  char *exp = malloc(700 * sizeof(char));
  int time=0;
  while (fscanf(fp, "%d %s\n", &result, exp) != -1)
  {
    // printf("%s\n",exp);
    bool ok = true;
    int res = (int)expr(exp, &ok);
    if (ok && result != res){
      printf("fail! %d/%d %s\n", res, result, exp);
      assert(0);
      }
    else
      printf("OK:%d\n",time++);
  }

#endif
  /* Start engine. */
  engine_start();

  return is_exit_status_bad();
}
