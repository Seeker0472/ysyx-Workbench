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
  if (getenv("NWM_APP")) {
    int fbctl = 4;
    fbdev = 5;
    screen_w = *w; screen_h = *h;
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
  }
}

void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) {
  // TOOD!!
  FILE*fb=fopen("/dev/fb","w");
  for (int i = 0; i < h; i++) {
    fseek(fb, ((i + y) * screen_w_h + x), SEEK_SET);
    fwrite(pixels+(w*i),sizeof(uint32_t),w,fb);
  }
  fclose(fb);
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
  // if (getenv("NWM_APP")) {
    evtdev = 3;
    fbdev = 4;
    dispinfodev = 5;
    read(dispinfodev, buffer, 0);
    sscanf(buffer,"WIDTH:%d\nHEIGHT:%d" , &screen_w_h,&screen_h_h);
    printf("WIDTH : %d\nHEIGHT:%d\n" , screen_w_h,screen_h_h);
  // }
  return 0;
}

void NDL_Quit() {
}
