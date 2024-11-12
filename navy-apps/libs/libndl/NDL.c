#include <assert.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

static int evtdev = -1;
static int fbdev = -1;
static int dispinfodev=-1;
static int screen_w = 0, screen_h = 0;
static int screen_w_h    = 0, screen_h_h = 0;

//returns ms
uint32_t NDL_GetTicks() {
  struct timeval stime;
  gettimeofday(&stime, NULL);
  return stime.tv_sec * 1000 + stime.tv_usec/1000;
}
// todo what the difference between fopen and open????
int NDL_PollEvent(char *buf, int len) {
  // FILE *fp = fopen("/dev/events", "r");
  // fseek(fp,0,SEEK_SET);
  // sprintf(buf, "1234");
  // return 0;
  int fp = open("/dev/events", O_RDONLY);
  return read(fp, buf, sizeof(buf) - 1);

}

void NDL_OpenCanvas(int *w, int *h) {
  // if (getenv("NWM_APP")) {
    // assert(0);
    int fbctl = 4;
    fbdev = 5;
    if(*w!=0&&*h!=0){
      screen_w = *w;
      screen_h = *h;
    } else {
      *w = screen_w = screen_w_h;
      *h = screen_h=screen_w_h;
    }
    assert(*w != 0 && *h != 0);
    //TODO!!!
    char buf[64];
    int len = sprintf(buf, "%d %d", screen_w, screen_h);
    // let NWM resize the window and create the frame buffer
    write(fbctl, buf, len);
    while (1) {
      // 3 = evtdev
      int nread = read(3, buf, sizeof(buf) - 1);
      if (nread <= 0) continue;
      buf[nread] = '\0';
      if (strcmp(buf, "mmap ok") == 0) break;
    }
    close(fbctl);
  // }
}

void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) {
  int fb = open("/dev/fb", O_WRONLY);
  printf("NDL:x:%xy:%xw:%xh:%x\n",x,y,w,h);
      // update_all
  if (x == 0 && y == 0 && w == screen_w_h && h == screen_h_h) {
    lseek(fb, 0, SEEK_SET);
    write(fb, pixels, w * h * sizeof(uint32_t));
    close(fb);
    return;
  }
  for (int i = 0; i < h; i++) {
    off_t offset = ((i + y) * screen_w_h + x) * sizeof(uint32_t);
    lseek(fb, offset, SEEK_SET);
    // write(fb, pixels + (w * i), w * sizeof(uint32_t));
    write(fb, pixels + (w * i), w * sizeof(uint32_t));
    // only pass w(not w * sizeof(uint32_t)) as the nemu io_write receive this
    // ==is this UB?
    // TODO
    // if use fwrite ,this func don't work---maybe copied to a buffer
  }
  close(fb);

}

void NDL_OpenAudio(int freq, int channels, int samples) {
}

void NDL_CloseAudio() {
}

int NDL_PlayAudio(void *buf, int len) {
  return 0;
}

int NDL_QueryAudio() {
  return 0;
}
//TODO
int NDL_Init(uint32_t flags) {
  char buffer[128];
// TODO: What NWM_APP????????
  // if (getenv("NWM_APP")) {
    evtdev = 3;
    fbdev = 4;
    dispinfodev = 5;
    read(dispinfodev, buffer, 0);
    sscanf(buffer,"WIDTH:%d\nHEIGHT:%d" , &screen_w_h,&screen_h_h);
    // printf("WIDTH : %d\nHEIGHT:%d\n" , screen_w_h,screen_h_h);
  // }
  return 0;
}

void NDL_Quit() {
}
