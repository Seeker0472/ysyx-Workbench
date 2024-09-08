# CROSS_COMPILE := riscv64-linux-gnu-
CROSS_COMPILE := riscv64-unknown-linux-gnu-
# 这里我修改了
COMMON_CFLAGS := -fno-pic -march=rv64g -mcmodel=medany -mstrict-align
# COMMON_CFLAGS := -fpic -march=rv64g -mcmodel=medany -mstrict-align
CFLAGS        += $(COMMON_CFLAGS) -static
ASFLAGS       += $(COMMON_CFLAGS) -O0
LDFLAGS       += -melf64lriscv

# overwrite ARCH_H defined in $(AM_HOME)/Makefile
ARCH_H := arch/riscv.h
