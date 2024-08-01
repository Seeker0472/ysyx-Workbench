#include "../include/ydb_all.h"
#include <stdint.h>
#include <stdio.h>

uint64_t get_time();
uint64_t time_now = 114514;


uint32_t mem_read(uint32_t pc);

uint32_t mem[0x800] = {
    0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493,
    0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493,
    0x00448493, 0x00448493, 0x00100073, 0x00448493, 0x00448493, 0x00448493,
    0x00448493, 0x00448493, 0x00448493,
};
uint32_t mrom[0x300] = {
    0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493,
    0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493,
    0x00448493, 0x00448493, 0x00100073, 0x00448493, 0x00448493, 0x00448493,
    0x00448493, 0x00448493, 0x00448493,
};
uint32_t flash[0x2000] = {
    0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493,
    0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493, 0x00448493,
    0x00448493, 0x00448493, 0x00100073, 0x00448493, 0x00448493, 0x00448493,
    0x00448493, 0x00448493, 0x00448493,
};

word_t mem_size = 84;

uint32_t mem_read(uint32_t pc) {
  if (pc == 0xa0000048) {
    time_now = get_time();
    // printf("%lx\n", time);
    return (uint32_t)time_now;
  }
  if (pc == 0xa000004c) {
    return (uint32_t)(time_now >> 32);
  }
  return mem[(pc - 0x80000000) / 4];
}

void init_mrom(char *img_file) {
  if(!img_file)
    return;
  int size = 0;
  FILE *fp = fopen(img_file, "rb");
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  fread(mrom, size, 1, fp);
  fclose(fp);
}

void init_flash() {
  for (int i = 0; i < 1000; i++) {
    flash[i] = i;
  }
}
void init_flash_img(char *img_file) {
  if(!img_file)
    return;
  int size = 0;
  FILE *fp = fopen(img_file, "rb");
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  fread(flash, size, 1, fp);
  fclose(fp);
}

void init_img(char *img_file) {
  // init_flash();
  // init_flash_img("/home/seeker/Develop/ysyx-workbench/npc/char-test.bin");
  init_flash_img(img_file);
  // init_mrom(img_file);
  // size_t size = 0;
  if (img_file != NULL) {
    //原本是把镜像加载进pmem中
    // FILE *fp = fopen(img_file, "rb");
    // // Assert(fp, "Can not open '%s'", img_file);
    // fseek(fp, 0, SEEK_END);
    // mem_size = ftell(fp);
    // // Log("The image is %s, size = %ld", img_file, size);
    // Log("The image is %s, size = %d", img_file, mem_size);
    // fseek(fp, 0, SEEK_SET);
    // int ret = fread(mem, mem_size, 1, fp);
    // // assert(ret == 1);
    // fclose(fp);
    // // return size;
  } else {
    Log("No Img file Loaded,Using Default IMG");
  }
}