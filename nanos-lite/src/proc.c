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
    Log("Hello World from Nanos-lite with arg '%p' for the %dth time!", (uintptr_t)arg, j);
    j ++;
    yield();
  }
}
void context_uload(PCB *pcb,const char *filename);
void naive_uload(PCB *pcb, const char *filename);
void init_proc() {
  switch_boot_pcb();

  Log("Initializing processes...");
  // naive_uload(NULL, "/bin/float");
  // "/share/games/nes/mario.nes"
  context_uload(&pcb[0], "/bin/menu");
  // load program here
}

Context *schedule(Context *prev) {
  Log("SHEDULE");
  int robin = 0;
  bool find=false;
  // find context,start robin
  //TODO:will not enter as pcb_boot.cp is NULL !!
  if (prev == pcb_boot.cp) {
    // first-boot
    for (int i = 0; i < MAX_NR_PROC; i++) {
      if (pcb[i].cp !=NULL) {
        robin = i;
        break;
      }
    }
  } else {
    for (int i = 0; i < MAX_NR_PROC; i++) {
      if (pcb[i].cp == prev) {
        robin = i;
        break;
      }
    }
    for (int i = (robin+1)%MAX_NR_PROC; true; i = (i + 1)%MAX_NR_PROC) {
      if (pcb[i].cp != NULL) {
        robin = i;
        find=true;
        break;
      }
    }
  }
  // Log("Going to %x",(uint32_t)pcb[robin].cp->mepc);
  if (!find)
    assert(0);
    // return prev;
  return pcb[robin].cp;
}
