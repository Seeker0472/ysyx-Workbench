#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000
static int key_f = 0, key_r = 0;
#define KEY_QUEUE_LEN 1024
static int key_queue[KEY_QUEUE_LEN] = {};


void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  int k = AM_KEY_NONE;

  if (key_f != key_r) {
    k = key_queue[key_f];
    key_f = (key_f + 1) % KEY_QUEUE_LEN;
  }

  kbd->keydown = (k & KEYDOWN_MASK ? true : false);
  kbd->keycode = k & ~KEYDOWN_MASK;
}