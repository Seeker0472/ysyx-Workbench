#include "gdbstub.h"
#include <stdio.h>
#include <assert.h>

static int nemu_read_reg(void *args, int regno, size_t *reg_value){
  return 0;
}
static int nemu_write_reg(void *args, int regno, size_t data){
  return 0;
}
static int nemu_read_mem(void *args, size_t addr, size_t len, void *val){
  return 0;
}
static int nemu_write_mem(void *args, size_t addr, size_t len, void *val){
  return 0;
}
static gdb_action_t nemu_cont(void *args){
  return 0;
}
static gdb_action_t nemu_stepi(void *args){
  return 0;
}
static bool nemu_set_bp(void *args, size_t addr, bp_type_t type){
  return 0;
}
static bool nemu_del_bp(void *args, size_t addr, bp_type_t type){
  return 0;
}
static void nemu_on_interrupt(void *args){
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
                          .reg_num = 32,
                          .reg_byte = 4,
                          .target_desc = TARGET_RV32,
                      },
                      "127.0.0.1:1234")) {
        fprintf(stderr, "Fail to create socket.\n");
        assert(0);
    }
}
void run_gdb(){
    if (!gdbstub_run(&gdbstub, (void *) NULL)) {
        fprintf(stderr, "Fail to run in debug mode.\n");
        assert(0);
    }
    gdbstub_close(&gdbstub);
  }
