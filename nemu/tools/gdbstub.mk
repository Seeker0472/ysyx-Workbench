LIB_GDBSTUB := $(NEMU_HOME)/tools/mini-gdbstub/build/libgdbstub.a

$(LIB_GDBSTUB):
	cd  $(NEMU_HOME)/tools/mini-gdbstub && make


.PHONY: $(LIB_GDBSTUB)
