#include <common.h>

#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void *buf, size_t offset, size_t len) {
  for (int i = 0; i < len; i++)
    putch(((const char *)buf)[i]);
  return len;
}

size_t events_read(void *buf, size_t offset, size_t len) {
   AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
  if (ev.keycode == AM_KEY_NONE) {
    return 0;
  } else {
    return sprintf(buf,"%s %s\n", ev.keydown ?"kd":"ku", keyname[ev.keycode]);
  }
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  // snprintf("WIDTH : 640\nHEIGHT:480", unsigned long, const char *, ...)
  AM_GPU_CONFIG_T gpuconfig;
  ioe_read(AM_GPU_CONFIG, &gpuconfig);
  if (gpuconfig.present) {
    return sprintf(buf,"WIDTH:%d\nHEIGHT:%d\n",gpuconfig.width,gpuconfig.height);
  }
  else
    return sprintf(buf, "WIDTH:640\nHEIGHT:480\n");
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  return 0;
}

void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
