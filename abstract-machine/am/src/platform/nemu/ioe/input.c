#include <am.h>
#include <nemu.h>
#include <stdint.h>
#include<stdio.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint32_t code = inw(KBD_ADDR);
  // printf("kbd->keydown=%d,,kbd->keycode=%d\n",(code & KEYDOWN_MASK ? true : false),code & ~KEYDOWN_MASK);
  kbd->keydown =  (code & KEYDOWN_MASK );
  uint32_t ps2_keycode = code & ~KEYDOWN_MASK; // TODO:翻译
  uint32_t am_keycode = 
}