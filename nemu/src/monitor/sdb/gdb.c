#include "gdbstub.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <cpu/cpu.h>
#include <isa.h>
#include <memory/paddr.h>


char *calc(){
  return "1234";
}

#define GenCSR(name, paddr) \
  "<reg name=\"" #name "\" bitsize=\"32\" type=\"int\" regnum=\"  \" />\n"



#define NEMU_CSR_TAGS \
  "<feature name=\"org.gnu.gdb.riscv.csr\">\n" \
  CSR_LIST \
  "</feature>\n"


void step(uint64_t n){
  cpu_exec(n);
}

// 	Run the emulator until hitting breakpoint or exit.
static gdb_action_t nemu_cont(void *args) { 
  step(-1);
  return ACT_RESUME; 
}
// Do one step on the emulator. You may define your own step for the emulator.
// For example, the common design is executing one instruction.
static gdb_action_t nemu_stepi(void *args) {
  //printf("STEP!\n");
  step(1);
  return ACT_RESUME; 
}
// Read the value of the register specified by regno to *value. Return zero if
// the operation success, otherwise return an errno for the corresponding error.
static int nemu_read_reg(void *args, int regno, size_t *reg_value) { 
  //printf("READ:%d\n",regno);
  if(regno>32){
    return 1;
  }
  *reg_value =  cpu.gpr[regno];
  return 0;
}
// Write value value to the register specified by regno. Return zero if the
// operation success, otherwise return an errno for the corresponding error.
static int nemu_write_reg(void *args, int regno, size_t data) { 
  if(regno>32){
    return 1;
  }
  cpu.gpr[regno]=data;
  return 0;
}
// Read the memory according to the address specified by addr with size len to
// the buffer *val. Return zero if the operation success, otherwise return an
// errno for the corresponding error.
static int nemu_read_mem(void *args, size_t addr, size_t len, void *val) {
  //printf("READMEM:%lx,len:%lx\n",addr,len);
  if(!in_pmem(addr)||!in_pmem((paddr_t)addr+len*4)){
    return 1;
  }
  uint8_t* host = guest_to_host(addr);
  memcpy(val, host, len);
  return 0;
}
// Write data in the buffer val with size len to the memory which address is
// specified by addr. Return zero if the operation success, otherwise return an
// errno for the corresponding error.
static int nemu_write_mem(void *args, size_t addr, size_t len, void *val) {
  if(!in_pmem(addr)||!in_pmem((paddr_t)addr+len*4)){
    return 1;
  }
  uint8_t* host = guest_to_host(addr);
  memcpy(host, val, len);
  return 0;
}
// Set type type breakpoint on the address specified by addr. Return true if we
// set the breakpoint successfully, otherwise return false.
static bool nemu_set_bp(void *args, size_t addr, bp_type_t type) {
  addr = addr&2?addr+2:addr;
  //printf("WATCH:%lx\n",addr);
  add_breakpoint(addr);
  return true; 
}
// Delete type type breakpoint on the address specified by addr. Return true if
// we delete the breakpoint successfully, otherwise return false.
static bool nemu_del_bp(void *args, size_t addr, bp_type_t type) {
  addr = addr&2?addr+2:addr;
  //printf("DEL_WATCH:%lx\n",addr);
  return delete_breakpoint(addr);
}
// Do something when receiving interrupt from GDB client. This method will run
// concurrently with cont, so you should be careful if there're shared data
// between them. You will need a lock or something similar to avoid data race.
static void nemu_on_interrupt(void *args) {
  printf("GDB_INTERRUPT\n");
  nemu_state.state=NEMU_STOP;
}

struct target_ops nemu_ops = {
    .read_reg = nemu_read_reg,
    .write_reg = nemu_write_reg,
    .read_mem = nemu_read_mem,
    .write_mem = nemu_write_mem,
    .cont = nemu_cont,
    .stepi = nemu_stepi,
    .set_bp = nemu_set_bp,
    .del_bp = nemu_del_bp,
    .on_interrupt = nemu_on_interrupt,
};
gdbstub_t gdbstub;
void init_gdb() {
  printf(NEMU_CSR_TAGS);
  if (!gdbstub_init(&gdbstub, &nemu_ops,
                    (arch_info_t){
                        .smp = 1,
                        .reg_num = 33,
                        .reg_byte = 4,
                        .target_desc = TARGET_RV32,
                    },
                    "127.0.0.1:1234")) {
    fprintf(stderr, "Fail to create socket.\n");
    assert(0);
  }
}
void run_gdb() {
  if (!gdbstub_run(&gdbstub, (void *)NULL)) {
    fprintf(stderr, "Fail to run in debug mode.\n");
    assert(0);
  }
  gdbstub_close(&gdbstub);
}
