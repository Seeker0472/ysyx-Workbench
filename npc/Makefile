# TOP
TOP ?=example

BUILD_DIR = ./build
TOP ?= core
PRJ = playground
TOP_NAME=V${TOP}
SED_CMD = sed -i "s/^.*\.v$$//"

ARGS ?=
IMG  ?=

ROOT_DIR := $(shell pwd)
# 这里是列举所有c/cpp/cc的绝对路径
SRC_DIR := csrc
# C_FILES := $(shell find $(SRC_DIR) -type f -name '*.c' )
ABS_C_FILES := $(shell find $(SRC_DIR) -type f -name '*.c' -exec realpath {} \;)
# CPP_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp' )
ABS_CPP_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp' -exec realpath {} \;)
# CC_FILES := $(shell find $(SRC_DIR) -type f -name '*.cc' )
ABS_CC_FILES := $(shell find $(SRC_DIR) -type f -name '*.cc' -exec realpath {} \;)
C_CPP_ABS := $(ABS_C_FILES) $(ABS_CPP_FILES) $(ABS_CC_FILES)

PERIP_V_ABS:=$(shell find $(YSYXSOC_HOME)/perip  -type f -name '*.v' -exec realpath {} \;)

ALL_V_ABS:=$(PERIP_V_ABS) ./build/ypc.sv $(YSYXSOC_HOME)/build/ysyxSoCFull.v

LINK_NEMU := --LDFLAGS -L${NEMU_HOME}/build/ --LDFLAGS ${NEMU_HOME}/build/riscv32-nemu-interpreter-so

CHISEL_SOURCES := $(shell find src -name '*.scala')
ABS_CHISEL_SOURCES := $(foreach src,$(CHISEL_SOURCES),$(realpath $(src)))
TARGET := build/ypc.sv

# $(shell llvm-config --cxxflags)
# deleted:::::   --CFLAGS -D__STDC_FORMAT_MACROS
CXXFLAGS := --CFLAGS -I/usr/lib/llvm-14/include --CFLAGS -std=c++14 --CFLAGS   -fno-exceptions --CFLAGS -D_GNU_SOURCE --CFLAGS -D__STDC_CONSTANT_MACROS  --CFLAGS -D__STDC_LIMIT_MACROS

FLAGS += --CFLAGS -I$(ROOT_DIR)/csrc/include/ --CFLAGS -save-temps --LDFLAGS -lreadline
FLAGS += ${CXXFLAGS} --CFLAGS -fPIE --LDFLAGS $(shell llvm-config --libs) ${LINK_NEMU}
# Verilator Includes list
FLAGS += -I$(YSYXSOC_HOME)/perip/uart16550/rtl -I$(YSYXSOC_HOME)/perip/spi/rtl
FLAGS += --timescale "1ns/1ns" --no-timing --autoflush

# CINCLUDE := $(ROOT_DIR)/csrc/main.cpp $(ROOT_DIR)/csrc/execute/exec.cpp $(ROOT_DIR)/csrc/memory/mem.cpp $(ROOT_DIR)/csrc/monitor/monitor.cpp

HINCLUDE := 

WAVEFORM_DIR := ${NPC_HOME}/build/waveform.vcd

include $(NPC_HOME)/scripts/conf.mk

# 仅仅当chisel代码发生变化的时候重新编译
$(TARGET): $(ABS_CHISEL_SOURCES)
	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mill -i $(PRJ).runMain Elaborate --target-dir $(BUILD_DIR)  --throw-on-first-error --full-stacktrace 
	$(SED_CMD) ./build/ypc.sv

test:
	mill -i $(PRJ).test

# 强制重新编译
verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mill -i $(PRJ).runMain Elaborate --target-dir $(BUILD_DIR)  --throw-on-first-error --full-stacktrace 
	$(SED_CMD) ./build/ypc.sv

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
	echo $(ALL_V_ABS)
	verilator -cc --top ysyxSoCFull $(ALL_V_ABS) --trace --exe  ${C_CPP_ABS}  ${FLAGS}
	make -j -C obj_dir -f VysyxSoCFull.mk VysyxSoCFull
	./obj_dir/VysyxSoCFull $(ARGS) $(IMG)

gdb:
	verilator -cc --top ysyxSoCFull $(ALL_V_ABS) --trace --exe  ${C_CPP_ABS}  --CFLAGS -g ${FLAGS} 
	make -j -C obj_dir -f VysyxSoCFull.mk VysyxSoCFull
	gdb   --args ./obj_dir/VysyxSoCFull $(ARGS) $(IMG)

wave:
	nohup /usr/bin/gtkwave ${WAVEFORM_DIR} > /dev/null 2>&1 &
all: $(TARGET) sim
	# @echo "所有文件的绝对路径："
	# @echo "$(C_CPP_ABS)"
-include ../Makefile

# TODO:　Batch-Mode amd more inst!!!!