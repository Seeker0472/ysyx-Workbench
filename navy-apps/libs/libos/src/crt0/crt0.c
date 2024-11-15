#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[], char *envp[]);
extern char **environ;
void call_main(uintptr_t *args) {
  char *empty[] =  {NULL };
  environ = empty;
  uint32_t argc = *(uint32_t *)args;
  char **argv = (char **)((uint32_t *)args + 1);
  char **envp = (char **)((uint32_t*)args+2+argc);
  exit(main(argc, argv, envp));
  assert(0);
}
