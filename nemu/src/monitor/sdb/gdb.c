#include "gdbstub.h"
#include <stdio.h>
#include <assert.h>

static int emu_read_reg(void *args, int regno, size_t *reg_value){
  return 0;
}
static int emu_write_reg(void *args, int regno, size_t data){
  return 0;
}
static int emu_read_mem(void *args, size_t addr, size_t len, void *val){
  return 0;
}
static int emu_write_mem(void *args, size_t addr, size_t len, void *val){
  return 0;
}
static gdb_action_t emu_cont(void *args){
  return 0;
}
static gdb_action_t emu_stepi(void *args){
  return 0;
}
static bool emu_set_bp(void *args, size_t addr, bp_type_t type){
  return 0;
}
static bool emu_del_bp(void *args, size_t addr, bp_type_t type){
  return 0;
}
static void emu_on_interrupt(void *args){
}

struct target_ops nemu_ops = {
    .read_reg = emu_read_reg,
    .write_reg = emu_write_reg,
    .read_mem = emu_read_mem,
    .write_mem = emu_write_mem,
    .cont = emu_cont,
    .stepi = emu_stepi,
    .set_bp = emu_set_bp,
    .del_bp = emu_del_bp,
    .on_interrupt = emu_on_interrupt,
};
gdbstub_t gdbstub;
void init_gdb() {
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
