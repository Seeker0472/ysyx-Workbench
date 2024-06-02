BUILD_DIR = ./build
NXDC_FILES = ./constr/example.nxdc
$(shell mkdir -p $(BUILD_DIR))
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

.DEFAULT_GOAL :=  all

all: sim verilating  run
	
verilating: $(SRC_AUTO_BIND)
	make nvboard-archive
# verilator -Wall -cc  vsrc/example.v --trace --exe csrc/main.cpp $(SRC_AUTO_BIND) -I$(NVBOARD_HOME)/include/nvboard.h
	verilator -MMD --build -cc -O3 --x-assign fast --x-initial fast --noassert \
	--top-module example /home/seeker/Develop/ysyx-workbench/npc/vsrc/example.v /home/seeker/Develop/ysyx-workbench/npc/csrc/main.cpp /home/seeker/Develop/ysyx-workbench/npc/build/auto_bind.cpp /home/seeker/Develop/ysyx-workbench/nvboard/build/nvboard.a \
	-CFLAGS -MMD -CFLAGS -O3 -CFLAGS -I/usr/include/SDL2 -CFLAGS -D_REENTRANT -CFLAGS -I/home/seeker/Develop/ysyx-workbench/nvboard/usr/include -CFLAGS -DTOP_NAME="\"Vexample\"" -LDFLAGS -lSDL2 -LDFLAGS -lSDL2_image -LDFLAGS -lSDL2_ttf \
	--Mdir ./build/obj_dir --exe -o /home/seeker/Develop/ysyx-workbench/npc/build/Vexample

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
# @echo "Write this Makefile by your self."

makeobj:
	make -C obj_dir/ -f Vexample.mk Vexample 
run:
	./build/Vexample
clean:
	rm -rf build/
include ../Makefile

