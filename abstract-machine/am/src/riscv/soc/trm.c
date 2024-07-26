#include <am.h>
#include <klib-macros.h>
#include "../riscv.h"

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (128 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

// #define SERIAL_PORT 0xa00003f8

void putch(char ch) {//实现putch
  outb(SERIAL_PORT, ch);
}

void halt(int code) {
  // code=1;
  // 将code加载到寄存器a0中，然后执行ebreak
  __asm__ volatile(
      "mv a0, %0\n" // 将code加载到a0寄存器
      "ebreak\n"    // 触发ebreak指令
      :             // 没有输出操作数
      : "r"(code)  // 输入操作数，将code传递给寄存器a0
      : "a0"        // 告诉编译器a0寄存器将被修改
  );
  while (1);
}

extern void * _data_section_start,*_data_section_end,*_data_section_dest;
void bootloader(){
  char * src=_data_section_start;
  char*dest=_data_section_dest;
  while(src<(char*)_data_section_end){
    *(dest++)=*(src++);
  }
}

void _trm_init() {
  bootloader();
  int ret = main(mainargs);
  halt(ret);
}
