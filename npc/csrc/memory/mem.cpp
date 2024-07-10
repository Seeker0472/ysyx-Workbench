#include <stdio.h>
#include <cstdint>
#include <debug.h>

void record_pread(paddr_t addr, int len);
void record_pwrite(paddr_t addr, int len, word_t data);
uint32_t mem[10000000]  = {
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
word_t mem_size=0;

uint32_t mem_read(uint32_t pc)
{
  // //mtrace
  // //TODO: Write  Enable-------------------------------------------------
  // record_pread(pc,4);
  return mem[(pc - 0x80000000) / 4];
}
uint32_t warp_pmem_read(uint32_t addr){
  return mem_read(addr);
}

void init_img(char *img_file)
{
  // size_t size = 0;
  if (img_file != NULL)
  {
    FILE *fp = fopen(img_file, "rb");
    // Assert(fp, "Can not open '%s'", img_file);
    fseek(fp, 0, SEEK_END);
    mem_size = ftell(fp);
    // Log("The image is %s, size = %ld", img_file, size);
    Log("The image is %s, size = %ld", img_file, mem_size);
    fseek(fp, 0, SEEK_SET);
    int ret = fread(mem, mem_size, 1, fp);
    // assert(ret == 1);
    fclose(fp);
    // return size;
  }
  else
  {
    Log("No Img file Loaded,Using Default IMG");
  }
}