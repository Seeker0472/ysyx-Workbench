BUILD_DIR = ./build
TOP ?= core
PRJ = playground
TOP_NAME=V${TOP}
SED_CMD = sed -i "s/^.*\.v$$//"

ARGS ?=
IMG  ?=

ROOT_DIR := $(shell pwd)
# 写的一坨大便！
SRC_DIR := csrc
C_FILES := $(shell find $(SRC_DIR) -type f -name '*.c' )
ABS_C_FILES := $(shell find $(SRC_DIR) -type f -name '*.c' -exec realpath {} \;)
CPP_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp' )
ABS_CPP_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp' -exec realpath {} \;)
CC_FILES := $(shell find $(SRC_DIR) -type f -name '*.cc' )
ABS_CC_FILES := $(shell find $(SRC_DIR) -type f -name '*.cc' -exec realpath {} \;)
C_CPP_ABS := $(ABS_C_FILES) $(ABS_CPP_FILES) $(ABS_CC_FILES)

LINK_NEMU := --CFLAGS -shared -o ${NEMU_HOME}/build/riscv32-nemu-interpreter-so 

# $(shell llvm-config --cxxflags)
# deleted:::::   --CFLAGS -D__STDC_FORMAT_MACROS
CXXFLAGS := --CFLAGS -I/usr/lib/llvm-14/include --CFLAGS -std=c++14 --CFLAGS   -fno-exceptions --CFLAGS -D_GNU_SOURCE --CFLAGS -D__STDC_CONSTANT_MACROS  --CFLAGS -D__STDC_LIMIT_MACROS

FLAGS += --CFLAGS -I$(ROOT_DIR)/csrc/include/ --CFLAGS -save-temps --LDFLAGS -lreadline
FLAGS += ${CXXFLAGS} --CFLAGS -fPIE --LDFLAGS $(shell llvm-config --libs) ${LINK_NEMU}

# CINCLUDE := $(ROOT_DIR)/csrc/main.cpp $(ROOT_DIR)/csrc/execute/exec.cpp $(ROOT_DIR)/csrc/memory/mem.cpp $(ROOT_DIR)/csrc/monitor/monitor.cpp

HINCLUDE := 

include $(NPC_HOME)/scripts/conf.mk

test:
	mill -i $(PRJ).test

verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mill -i $(PRJ).runMain Elaborate --target-dir $(BUILD_DIR)  --throw-on-first-error --full-stacktrace 
	$(SED_CMD) ./build/core.sv

help:
	mill -i $(PRJ).runMain Elaborate --help

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat

clean:
	-rm -rf $(BUILD_DIR)
	-rm -rf obj_dir

.PHONY: test verilog help reformat checkformat clean

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	# @echo "Write this Makefile by yourself."
	
	verilator -cc --top core  ./build/core.sv --trace --exe  ${C_CPP_ABS}  ${FLAGS}
	make -j -C obj_dir -f Vcore.mk Vcore
	./obj_dir/Vcore $(ARGS) $(IMG)

gdb:
	verilator -cc --top core  ./build/core.sv --trace --exe  ${C_CPP_ABS}  --CFLAGS -g ${FLAGS}
	make -j -C obj_dir -f Vcore.mk Vcore
	gdb   --args ./obj_dir/Vcore  $(ARGS) $(IMG)
all: verilog sim
	# @echo "所有 .c 文件的绝对路径："
	# @echo "$(C_CPP_ABS)"
-include ../Makefile

# TODO:　Batch-Mode amd more inst!!!!
