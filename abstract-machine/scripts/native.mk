AM_SRCS := native/trm.c \
           native/ioe.c \
           native/cte.c \
           native/trap.S \
           native/vme.c \
           native/mpe.c \
           native/platform.c \
           native/ioe/input.c \
           native/ioe/timer.c \
           native/ioe/gpu.c \
           native/ioe/uart.c \
           native/ioe/audio.c \
           native/ioe/disk.c \

CFLAGS  += -fpie
ASFLAGS += -fpie -pie
comma = ,
LDFLAGS_CXX = $(addprefix -Wl$(comma), $(LDFLAGS))

image:
	@echo + LD "->" $(IMAGE_REL)
	g++ -g -pie  -o $(IMAGE) -Wl,--whole-archive $(LINKAGE) -Wl,-no-whole-archive $(LDFLAGS_CXX) -lSDL2 -ldl -g

run: image
	$(IMAGE)

gdb: image
	gdb $(IMAGE)
