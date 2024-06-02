
all:clean verilating makeobj run sim
	
verilating:
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

