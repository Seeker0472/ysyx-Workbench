#include <am.h>
#include "../riscv.h"
#include "stdio.h"

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  bool have_code = (inb(SERIAL_PORT + 5) & 0x1) == 1;
  uint32_t code = have_code ? inb(SERIAL_PORT) : AM_KEY_NONE;
  if (have_code == 1)
    putch('A');
  kbd->keydown = 0;
  kbd->keycode = code;
}
