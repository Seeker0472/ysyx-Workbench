# TOP
include $(NVBOARD_HOME)/scripts/nvboard.mk
TOP ?=example

BUILD_DIR = ./build
TOP ?= core
PRJ = playground
TOP_NAME=V${TOP}
SED_CMD = sed -i "s/^.*\.v$$//"
NXDC_FILE = ${NPC_HOME}/csrc/nvb/soc.nxdc
SRC_AUTO_BIND = ${NPC_HOME}/csrc/nvb/bind.cpp
YSYXSOC_V := $(YSYXSOC_HOME)/build/ysyxSoCFull.v

ARGS ?=
IMG  ?=

ROOT_DIR := $(shell pwd)
# 这里是列举所有c/cpp/cc的绝对路径
SRC_DIR := csrc
ABS_C_FILES := $(shell find $(SRC_DIR) -type f -name '*.c' -exec realpath {} \;)
ABS_CPP_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp' -exec realpath {} \;)
ABS_CC_FILES := $(shell find $(SRC_DIR) -type f -name '*.cc' -exec realpath {} \;)
C_CPP_ABS := $(ABS_C_FILES) $(ABS_CPP_FILES) $(ABS_CC_FILES)

PERIP_V_ABS:=$(shell find $(YSYXSOC_HOME)/perip  -type f -name '*.v' -exec realpath {} \;)
SOC_SCALA_ABS:=$(shell find $(YSYXSOC_HOME)/src  -type f -name '*.scala' -exec realpath {} \;)

ALL_V_ABS:=$(PERIP_V_ABS) ./build/ypc.sv ${YSYXSOC_V}

ABS_CHISEL_SOURCES := $(shell find src -type f -name '*.scala' -exec realpath {} \;)
TARGET := build/ypc.sv

# VCXXFLAGS += --CFLAGS -std=c++14 

#cincludes --CFLAGS
CFLAGS := -I/usr/lib/llvm-14/include -I$(ROOT_DIR)/csrc/include/
CFLAGS += -I$(NVBOARD_HOME)/usr/include
# sdls 
# CFLAGS += -I/usr/include/SDL2
CFLAGS +=  $(shell pkg-config --cflags sdl2) $(shell pkg-config --cflags SDL2_image) $(shell pkg-config --cflags SDL2_ttf)
CFLAGS += -save-temps -fPIE -fno-exceptions

LDFLAGS += -L${NEMU_HOME}/build/ ${NEMU_HOME}/build/riscv32-nemu-interpreter-so #NEMU
LDFLAGS += $(shell llvm-config --libs) #llvm
LDFLAGS += -lreadline #readline

LDFLAGS += -L${NVBOARD_HOME}/build/ ${NVBOARD_HOME}/build/nvboard.a -lSDL2 -lSDL2_image -lSDL2_ttf #NVBoard

# Verilator Includes list
FLAGS += -I$(YSYXSOC_HOME)/perip/uart16550/rtl -I$(YSYXSOC_HOME)/perip/spi/rtl
FLAGS += --timescale "1ns/1ns" --no-timing --autoflush
FLAGS += -j 8	--compiler gcc

HINCLUDE := 

WAVEFORM_DIR := ${NPC_HOME}/build/waveform.vcd

include $(NPC_HOME)/scripts/conf.mk

CFLAGS := $(foreach flag,$(CFLAGS),--CFLAGS $(flag))
LDFLAGS := $(foreach flag,$(LDFLAGS),--LDFLAGS $(flag))

FLAGS += $(CFLAGS) $(LDFLAGS)

# 仅仅当chisel代码发生变化的时候重新编译
$(TARGET): $(ABS_CHISEL_SOURCES)
	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mill -i $(PRJ).runMain Elaborate --target-dir $(BUILD_DIR)  --throw-on-first-error --full-stacktrace 
	$(SED_CMD) ./build/ypc.sv

$(SRC_AUTO_BIND): $(NXDC_FILE)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

$(YSYXSOC_V): $(SOC_SCALA_ABS)
	make -C $(YSYXSOC_HOME) verilog

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

sim: $(YSYXSOC_V) $(SRC_AUTO_BIND)
	# $(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator -cc --top ysyxSoCFull $(ALL_V_ABS) --trace --exe  ${C_CPP_ABS}  ${FLAGS} -Wno-WIDTHEXPAND
	make -C obj_dir -f VysyxSoCFull.mk VysyxSoCFull
	./obj_dir/VysyxSoCFull $(ARGS) $(IMG)

gdb: $(YSYXSOC_V) $(SRC_AUTO_BIND)
	@verilator -cc --top ysyxSoCFull $(ALL_V_ABS) --trace --exe  ${C_CPP_ABS}  --CFLAGS -g ${FLAGS} 
	@make -j -C obj_dir -f VysyxSoCFull.mk VysyxSoCFull
	gdb   --args ./obj_dir/VysyxSoCFull $(ARGS) $(IMG)

wave:
	# nohup /usr/bin/gtkwave ${WAVEFORM_DIR} > /dev/null 2>&1 &
	nohup gtkwave ${WAVEFORM_DIR} > /dev/null 2>&1 &
all: $(TARGET) sim

-include ../Makefile
