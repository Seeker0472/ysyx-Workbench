#include "../riscv.h"
#include "stdio.h"
#include <am.h>

#define KEYDOWN_MASK 0xff00
#define KBD_ADDR 0x10011000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint32_t code = inw(KBD_ADDR);
  printf("kbd->keydown=%d,,kbd->keycode=%d\n",(code & KEYDOWN_MASK ? true :
  false),code & ~KEYDOWN_MASK);
  kbd->keydown = (code & KEYDOWN_MASK);
  kbd->keycode = code & ~KEYDOWN_MASK;
}
