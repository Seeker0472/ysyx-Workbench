#include "gdbstub.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <cpu/cpu.h>
#include <isa.h>
#include <memory/paddr.h>

#define GenCSR(name, paddr) \
  "<reg name=\"" #name "\" bitsize=\"32\" type=\"int\" regnum=\"" #paddr "\" />\n"

#define NEMU_CSR_TAGS \
  "<feature name=\"org.gnu.gdb.riscv.csr\">\n" \
  CSR_LIST \
  "</feature>\n"

#define NEMU_REG_TAGS \
    "<feature name=\"org.gnu.gdb.riscv.cpu\">" \
    "<reg name=\"zero\" bitsize=\"32\" type=\"int\" regnum=\"0\"/>" \
    "<reg name=\"RA\" bitsize=\"32\" type=\"code_ptr\" regnum=\"1\"/>" \
    "<reg name=\"sp\" bitsize=\"32\" type=\"data_ptr\" regnum=\"2\"/>" \
    "<reg name=\"gp\" bitsize=\"32\" type=\"data_ptr\" regnum=\"3\"/>" \
    "<reg name=\"tp\" bitsize=\"32\" type=\"data_ptr\" regnum=\"4\"/>" \
    "<reg name=\"t0\" bitsize=\"32\" type=\"int\" regnum=\"5\"/>" \
    "<reg name=\"t1\" bitsize=\"32\" type=\"int\" regnum=\"6\"/>" \
    "<reg name=\"t2\" bitsize=\"32\" type=\"int\" regnum=\"7\"/>" \
    "<reg name=\"fp\" bitsize=\"32\" type=\"data_ptr\" regnum=\"8\"/>" \
    "<reg name=\"s1\" bitsize=\"32\" type=\"int\" regnum=\"9\"/>" \
    "<reg name=\"a0\" bitsize=\"32\" type=\"int\" regnum=\"10\"/>" \
    "<reg name=\"a1\" bitsize=\"32\" type=\"int\" regnum=\"11\"/>" \
    "<reg name=\"a2\" bitsize=\"32\" type=\"int\" regnum=\"12\"/>" \
    "<reg name=\"a3\" bitsize=\"32\" type=\"int\" regnum=\"13\"/>" \
    "<reg name=\"a4\" bitsize=\"32\" type=\"int\" regnum=\"14\"/>" \
    "<reg name=\"a5\" bitsize=\"32\" type=\"int\" regnum=\"15\"/>" \
    "<reg name=\"a6\" bitsize=\"32\" type=\"int\" regnum=\"16\"/>" \
    "<reg name=\"a7\" bitsize=\"32\" type=\"int\" regnum=\"17\"/>" \
    "<reg name=\"s2\" bitsize=\"32\" type=\"int\" regnum=\"18\"/>" \
    "<reg name=\"s3\" bitsize=\"32\" type=\"int\" regnum=\"19\"/>" \
    "<reg name=\"s4\" bitsize=\"32\" type=\"int\" regnum=\"20\"/>" \
    "<reg name=\"s5\" bitsize=\"32\" type=\"int\" regnum=\"21\"/>" \
    "<reg name=\"s6\" bitsize=\"32\" type=\"int\" regnum=\"22\"/>" \
    "<reg name=\"s7\" bitsize=\"32\" type=\"int\" regnum=\"23\"/>" \
    "<reg name=\"s8\" bitsize=\"32\" type=\"int\" regnum=\"24\"/>" \
    "<reg name=\"s9\" bitsize=\"32\" type=\"int\" regnum=\"25\"/>" \
    "<reg name=\"s10\" bitsize=\"32\" type=\"int\" regnum=\"26\"/>" \
    "<reg name=\"s11\" bitsize=\"32\" type=\"int\" regnum=\"27\"/>" \
    "<reg name=\"t3\" bitsize=\"32\" type=\"int\" regnum=\"28\"/>" \
    "<reg name=\"t4\" bitsize=\"32\" type=\"int\" regnum=\"29\"/>" \
    "<reg name=\"t5\" bitsize=\"32\" type=\"int\" regnum=\"30\"/>" \
    "<reg name=\"t6\" bitsize=\"32\" type=\"int\" regnum=\"31\"/>" \
    "<reg name=\"pc\" bitsize=\"32\" type=\"code_ptr\" regnum=\"32\"/>" \
  "</feature>"

#define NEMU_OTHER_TAGS \
    "<feature name=\"org.gnu.gdb.riscv.virtual\">" \
    "<reg name=\"PRIV\" bitsize=\"32\" type=\"int\" regnum=\"65\"/>" \
  "</feature>"

#define NEMU_FEATURES \
  "<target version=\"1.0\"><architecture>riscv:rv32</architecture>"  \
  NEMU_REG_TAGS \
  NEMU_OTHER_TAGS \
  NEMU_CSR_TAGS \
  "</target>"

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
  if(regno==65){
    *reg_value=cpu.PRIV;
    return 0;
  }
  if(regno>32){
    if(regno<4096){
      *reg_value=cpu.csr[regno];
      return 0;
    }
    return 1;
  }
  *reg_value =  cpu.gpr[regno];
  return 0;
}
// Write value value to the register specified by regno. Return zero if the
// operation success, otherwise return an errno for the corresponding error.
static int nemu_write_reg(void *args, int regno, size_t data) { 
  if(regno==65){
    cpu.PRIV=data;
    return 0;
  }
  if(regno>32){
    if(regno<4096){
      cpu.csr[regno]=data;
      return 0;
    }
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
  if (!gdbstub_init(&gdbstub, &nemu_ops,
                    (arch_info_t){
                        .smp = 1,
                        .reg_num = 33,
                        .reg_byte = 4,
                        .target_desc = NEMU_FEATURES,
                    },
                    "127.0.0.1:1234")) {
                   // "/tmp/gdbstub.sock")) {
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
