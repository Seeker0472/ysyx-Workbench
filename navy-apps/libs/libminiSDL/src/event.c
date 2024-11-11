#include "fcntl.h"
#include "sdl-event.h"
#include "unistd.h"
#include <NDL.h>
#include <SDL.h>
#include <string.h>

#define keyname(k) #k,

static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};

int SDL_PushEvent(SDL_Event *ev) {
  return 0;
}

int SDL_PollEvent(SDL_Event *ev) {
  return 0;
}

int SDL_WaitEvent(SDL_Event *event) {
  // return 1;
  char buffer[100];
  while (1) {
    int fd = open("/dev/events", O_RDONLY);
    if (read(fd, buffer, 100)) {
      event->key.keysym.sym = SDLK_J;
      event->type=SDL_KEYDOWN;
    }
    return 1;
  }
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}
