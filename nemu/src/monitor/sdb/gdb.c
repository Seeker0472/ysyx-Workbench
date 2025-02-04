#include "gdbstub.h"
#include <assert.h>
#include <stdio.h>

// 	Run the emulator until hitting breakpoint or exit.
static gdb_action_t nemu_cont(void *args) { return ACT_RESUME; }
// Do one step on the emulator. You may define your own step for the emulator.
// For example, the common design is executing one instruction.
static gdb_action_t nemu_stepi(void *args) { return ACT_RESUME; }
// Read the value of the register specified by regno to *value. Return zero if
// the operation success, otherwise return an errno for the corresponding error.
static int nemu_read_reg(void *args, int regno, size_t *reg_value) { return 0; }
// Write value value to the register specified by regno. Return zero if the
// operation success, otherwise return an errno for the corresponding error.
static int nemu_write_reg(void *args, int regno, size_t data) { return 0; }
// Read the memory according to the address specified by addr with size len to
// the buffer *val. Return zero if the operation success, otherwise return an
// errno for the corresponding error.
static int nemu_read_mem(void *args, size_t addr, size_t len, void *val) {
  return 0;
}
// Write data in the buffer val with size len to the memory which address is
// specified by addr. Return zero if the operation success, otherwise return an
// errno for the corresponding error.
static int nemu_write_mem(void *args, size_t addr, size_t len, void *val) {
  return 0;
}
// Set type type breakpoint on the address specified by addr. Return true if we
// set the breakpoint successfully, otherwise return false.
static bool nemu_set_bp(void *args, size_t addr, bp_type_t type) { return 0; }
// Delete type type breakpoint on the address specified by addr. Return true if
// we delete the breakpoint successfully, otherwise return false.
static bool nemu_del_bp(void *args, size_t addr, bp_type_t type) { return 0; }
// Do something when receiving interrupt from GDB client. This method will run
// concurrently with cont, so you should be careful if there're shared data
// between them. You will need a lock or something similar to avoid data race.
static void nemu_on_interrupt(void *args) {}

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
                        .reg_num = 32,
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
