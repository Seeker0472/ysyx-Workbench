BUILD_DIR = ./build
NXDC_FILES = ./constr/example.nxdc
$(shell mkdir -p $(BUILD_DIR))
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

.DEFAULT_GOAL :=  all

all:clean verilating makeobj run sim
	
verilating: $(SRC_AUTO_BIND)
	verilator -Wall -cc  vsrc/example.v --trace --exe csrc/main.cpp

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
# @echo "Write this Makefile by your self."

makeobj:
	make -C obj_dir/ -f Vexample.mk Vexample
run:
	./obj_dir/Vexample
clean:
	rm -rf obj_dir/
include ../Makefile

