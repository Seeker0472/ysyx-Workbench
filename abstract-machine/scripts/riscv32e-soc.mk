include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/soc.mk
# CFLAGS  += -DISA_H=\"riscv/soc.h\"
COMMON_CFLAGS += -march=rv32e_zicsr_zifencei -mabi=ilp32e  # overwrite
LDFLAGS       += -melf32lriscv                    # overwrite
LDFLAGS       += -Map output.map

AM_SRCS += riscv/npc/libgcc/div.S \
           riscv/npc/libgcc/muldi3.S \
           riscv/npc/libgcc/multi3.c \
           riscv/npc/libgcc/ashldi3.c \
           riscv/npc/libgcc/unused.c