LIB_GDBSTUB := $(NEMU_HOME)/tools/mini-gdbstub/build/libgdbstub.a

LDFLAGS += -L $(LIB_GDBSTUB)

ifndef CONFIG_DIFFTEST_REF_NEMU
$(LIB_GDBSTUB):
	cd $(NEMU_HOME)/tools/mini-gdbstub && make
endif

.PHONY: $(LIB_GDBSTUB)
