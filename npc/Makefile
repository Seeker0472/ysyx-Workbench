BUILD_DIR = ./build
TOP ?= core
PRJ = playground
TOP_NAME=V${TOP}
SED_CMD = sed -i "s/^.*\.v$$//"

ARGS ?=

ROOT_DIR := $(shell pwd)

CINCLUDE := $(ROOT_DIR)/csrc/main.cpp $(ROOT_DIR)/csrc/execute/exec.cpp $(ROOT_DIR)/csrc/memory/mem.cpp $(ROOT_DIR)/csrc/monitor/monitor.cpp

HINCLUDE := 

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

.PHONY: test verilog help reformat checkformat clean

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	# @echo "Write this Makefile by yourself."
	
	verilator -cc --top core  ./build/core.sv --trace --exe  ${CINCLUDE} -I$(ROOT_DIR)/csrc/include/
	make -j -C obj_dir -f Vcore.mk Vcore
	./obj_dir/Vcore $(ARGS) $(IMG)

all: verilog sim
-include ../Makefile
