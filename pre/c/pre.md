# typing-game执行细节

## 编译阶段

- Makefile里面设定NAME CSRC,Include AM_Makefile

### Makefile-AbstractMachine

#### Stage1-初始化和检查

- 设置默认MAKECMDGOALS为image
- 检查AM_HOME
- 检查ARCH是否有对应的makefile

#### Stage2-获取编译/链接对象

- 立即展开(:=)和延迟展开(=)困扰了很久
- 创建build-dir 为编译/链接对象赋值

#### Stage3-生成编译参数

- 这里曾经导致我的LSP配不好
- ISA,ARCH,PLATFORM等参数在这里以宏定义形式传递给编译器

#### Stage4-include指定架构参数

include scripts/.mk

##### in included file

- include riscv.mk - 主要是交叉编译器和编译参数
- include platform/npc.mk - AM_SRCS-am的源代码文件列表,链接脚本,还有image,run,gdb的target

#### Stage5-编译链接规则

- recursive make--for am,klib...
- 其他没什么好讲的了解一下各个参数的意思
- 还有一个include--自动依赖!!!这个可以认真讲一下

```
$(DST_DIR)/%.o: %.c
	@mkdir -p $(dir $@) && echo + CC $<
	@$(CC) -std=gnu11 $(CFLAGS) -c -o $@ $(realpath $<)
```

#### 杂项(其实我还没怎么用过:-))

- image
- archive
- image-dep
- clean
- clean-all

and whatthe fxxking .PHONY means??

## 运行阶段NEMU/NPC(TODO)

观察的角度

- 站在现在的角度(已经对AM的代码有一定的了解),直接RTFM--自顶向下,自顶向上
- 站在过去的角度,使用工具的角度 代码跳转,gdb 慢慢调,ftrace,编译器宏展开其实有点难用,clangd宏展开已经很好用了?

什么是计算机? 为何叫Abstract-Mashine?AM的设计如何??
硬件和软件之间的隔阂/类同

软件/计算机的抽象!

- 站在NEMU的角度
- 站在AM的角度

- ioe_init

### AM

#### REGS

- AM_TIMER_CONFIG
- AM_INPUT_CONFIG
- AM_TIMER_UPTIME-reg
- AM_GPU_FBDRAW

#### AM-HARDWARE

执行ioe-read/ioe-write -> 执行对应的函数
抽象寄存器实际上是函数return的struct

### klib

- printf
- putch
- rand

### graf

```text

###########################
	program
###########################
	AM       Klib
###########################
NEMU ## native ## Soc/nvboard
###########################
物理机

```

## 比较抽象的Bug

缓冲区溢出
