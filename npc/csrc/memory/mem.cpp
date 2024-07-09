#include <stdio.h>
#include <cstdint>
#include <debug.h>
static uint32_t mem[10000000]  = {
    0x00448493,
    0x00448493,
    0x00100073,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
};

uint32_t mem_read(int pc)
{
  return mem[(pc - 0x80000000) / 4];
}


void init_img(char *img_file)
{
  if (img_file != NULL)
  {
    FILE *fp = fopen(img_file, "rb");
    // Assert(fp, "Can not open '%s'", img_file);
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    // Log("The image is %s, size = %ld", img_file, size);
    Log("The image is %s, size = %ld", img_file, size);
    fseek(fp, 0, SEEK_SET);
    int ret = fread(mem, size, 1, fp);
    // assert(ret == 1);
    fclose(fp);
    // return size;
  }
  else
  {
    Log("No Img file Loaded,Using Default IMG");
  }
}