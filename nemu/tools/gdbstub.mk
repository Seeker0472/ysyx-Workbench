LIB_GDBSTUB := $(NEMU_HOME)/tools/mini-gdbstub/build/libgdbstub.a

$(LIB_GDBSTUB):
	echo 12334
	cd $(NEMU_HOME)/tools/mini-gdbstub && make


.PHONY: $(LIB_GDBSTUB)
