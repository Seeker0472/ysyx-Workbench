include $(NVBOARD_HOME)/scripts/nvboard.mk
BUILD_DIR = ./build
PRJ = npc_chisel
SED_CMD = sed -i "s/^.*\.v$$//"
NXDC_FILE = ${NPC_HOME}/nvboardbind/soc.nxdc
SRC_AUTO_BIND = ${NPC_HOME}/nvboardbind/bind.cpp
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
TARGETRaw := build/raw_core.sv

# VCXXFLAGS += --CFLAGS -std=c++14 

#cincludes --CFLAGS
NPC_CFLAGS += -I/usr/lib/llvm-14/include -I$(ROOT_DIR)/csrc/include/
NPC_CFLAGS += -save-temps -fPIE -fno-exceptions
NPC_CFLAGS_SOC += $(NPC_CFLAGS) -I$(NVBOARD_HOME)/usr/include

# sdls 
# NPC_CFLAGS += -I/usr/include/SDL2
NPC_CFLAGS_SOC += $(shell pkg-config --cflags sdl2) $(shell pkg-config --cflags SDL2_image) $(shell pkg-config --cflags SDL2_ttf)

# common NPC_LDFLAGS
NPC_LDFLAGS += -L${NEMU_HOME}/build/ ${NEMU_HOME}/build/riscv32-nemu-interpreter-so #NEMU
NPC_LDFLAGS += $(shell llvm-config --libs) #llvm
NPC_LDFLAGS += -lreadline #readline

NPC_LDFLAGS_SOC += $(NPC_LDFLAGS) -L${NVBOARD_HOME}/build/ ${NVBOARD_HOME}/build/nvboard.a -lSDL2 -lSDL2_image -lSDL2_ttf #NVBoard

WAVEFORM_DIR := ${NPC_HOME}/build/waveform.vcd ${NPC_HOME}/build/wave.gtkw

include $(NPC_HOME)/scripts/conf.mk

# NPC_CFLAGS := $(foreach flag,$(NPC_CFLAGS),--CFLAGS $(flag))
# NPC_LDFLAGS := $(foreach flag,$(NPC_LDFLAGS),--LDFLAGS $(flag))
NPC_CFLAGS_SOC := $(foreach flag,$(NPC_CFLAGS_SOC),--CFLAGS $(flag))
NPC_LDFLAGS_SOC := $(foreach flag,$(NPC_LDFLAGS_SOC),--LDFLAGS $(flag))

NPC_CFLAGS += -DNPC

NPC_CFLAGS := $(foreach flag,$(NPC_CFLAGS),--CFLAGS $(flag))
NPC_LDFLAGS := $(foreach flag,$(NPC_LDFLAGS),--LDFLAGS $(flag))

FLAGS += $(NPC_CFLAGS) $(NPC_LDFLAGS)
FLAGS_SOC += $(NPC_CFLAGS_SOC) $(NPC_LDFLAGS_SOC)

FLAGS += -j 8  -Mdir build/npc_build

FLAGS_SOC += -I$(YSYXSOC_HOME)/perip/uart16550/rtl -I$(YSYXSOC_HOME)/perip/spi/rtl
FLAGS_SOC += --timescale "1ns/1ns" --no-timing --autoflush -Mdir build/soc_build -j 8

# 仅仅当chisel代码发生变化的时候重新编译
$(TARGET): $(ABS_CHISEL_SOURCES)
	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mill -i $(PRJ).runMain Elaborate --target-dir $(BUILD_DIR)  --throw-on-first-error --full-stacktrace 
	$(SED_CMD) ./build/ypc.sv

$(TARGETRaw): $(ABS_CHISEL_SOURCES)
	mkdir -p $(BUILD_DIR)
	PC_VALUE="h80000000" mill -i $(PRJ).runMain ElaborateRaw --target-dir $(BUILD_DIR)  --throw-on-first-error --full-stacktrace 
	$(SED_CMD) $(TARGETRaw)

$(SRC_AUTO_BIND): $(NXDC_FILE)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

$(YSYXSOC_V): $(SOC_SCALA_ABS)
	make -C $(YSYXSOC_HOME) verilog

test:
	mill -i $(PRJ).test

# 强制重新编译
verilog:
	# $(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mill -i $(PRJ).runMain Elaborate --target-dir $(BUILD_DIR)   --throw-on-first-error --full-stacktrace 
	$(SED_CMD) ./build/ypc.sv

help:
	mill -i $(PRJ).runMain Elaborate --help

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat

clean:
	-rm -rf $(BUILD_DIR)
	# -rm -rf obj_dir
	# -rm -rf obj_dir_npc

.PHONY: test verilog help reformat checkformat clean

sim: $(TARGET) $(YSYXSOC_V) $(SRC_AUTO_BIND)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@verilator -cc --top ysyxSoCFull $(ALL_V_ABS) --trace --exe  ${C_CPP_ABS} ${SRC_AUTO_BIND} ${FLAGS_SOC} 
	@make -j -C build/soc_build -f VysyxSoCFull.mk VysyxSoCFull
	./build/soc_build/VysyxSoCFull $(ARGS) $(IMG)

simnpc:$(TARGETRaw)
	@verilator -cc --top raw_core $(TARGETRaw) --trace --exe  ${C_CPP_ABS}  ${FLAGS} -Wno-WIDTHEXPAND
	@make -j -C build/npc_build -f Vraw_core.mk Vraw_core
	./build/npc_build/Vraw_core $(ARGS) $(IMG)

gdbnpc:$(TARGETRaw)
	@verilator -cc --top raw_core $(TARGETRaw) --trace --exe  ${C_CPP_ABS} --CFLAGS -g ${FLAGS} -Wno-WIDTHEXPAND -O1 --autoflush
	@make -j -C build/npc_build -f Vraw_core.mk Vraw_core
	gdb   --args ./build/npc_build/Vraw_core $(ARGS) $(IMG)

gdb: $(TARGET) $(YSYXSOC_V) $(SRC_AUTO_BIND)
# 这里的－Ｏ１是避免编译器过度优化导致无法正常ｇｄｂ调试
	@verilator  -cc --top ysyxSoCFull $(ALL_V_ABS) --trace --exe  ${C_CPP_ABS} ${SRC_AUTO_BIND} --CFLAGS -g ${FLAGS_SOC} -O1 --autoflush
	@make -j -C build/soc_build -f VysyxSoCFull.mk VysyxSoCFull
	gdb --args ./build/soc_build/VysyxSoCFull $(ARGS) $(IMG)

wave:
	# nohup /usr/bin/gtkwave ${WAVEFORM_DIR} > /dev/null 2>&1 &
	nohup gtkwave ${WAVEFORM_DIR} > /dev/null 2>&1 &
all: $(TARGET) sim

sta: $(TARGET)
	@cd ./tools/py && python3 rm_dpic.py
	mv build/ypc_nodpic.sv ../yosys-sta/ypc/ypc.sv
	cd ../yosys-sta/ && make sta
	cd ./tools/py && python3 update_freq.py
	cd ./tools/py && python3 get_area.py


-include ../Makefile
