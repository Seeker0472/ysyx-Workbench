#include <stdio.h>
#include <cstdint>
#include <debug.h>
#include <common.h>
#include <isa.h>
#include <macro.h>

uint64_t get_time();
uint64_t time_now = 114514;

void record_pread(paddr_t addr, int len);
void record_pwrite(paddr_t addr, char wmask, word_t data);
uint32_t mem_read(uint32_t pc);

uint32_t mem[0x8000000] = {
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
    0x00100073,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
};
uint32_t mrom[0x300] = {
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
    0x00100073,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
};
uint32_t flash[0x2000]={};

word_t mem_size = 84;

// DPI-C Funcs
extern "C" void flash_read(int32_t addr, int32_t *data) {
  printf("%x\n",addr);
  // *data=flash[addr/4];
  *data=0xf;
 }
extern "C" void mrom_read(int32_t addr, int32_t *data) { 
  *data= mrom[(addr - 0x20000000) / 4];
}

extern "C" int get_time(int raddr)
{
  if (raddr == 0x10000048)
  {
    time_now = get_time();
    return (uint32_t)time_now;
  }
  if (raddr == 0x1000004c)
  {
    return (uint32_t)(time_now >> 32);
  }
  return -1;
}

extern "C" int pmem_read(int raddr)
{
  // 总是读取地址为`raddr & ~0x3u`的4字节返回
  // Log("mem_read");
  int aligned_addr = raddr & ~0x3u; // 对齐地址
  IFDEF(CONFIG_MTRACE, record_pread(raddr, 4););

  return mem_read(aligned_addr);
}
extern "C" void pmem_write(int waddr, int wdata, char wmask)
{
  // 总是往地址为`waddr & ~0x3u`的4字节按写掩码`wmask`写入`wdata`
  // `wmask`中每比特表示`wdata`中1个字节的掩码,
  // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
  // Log("mem_write");
  // int length = 0;
  // for (int i = 0; i < 4; i++)
  //   if (wdata & (3 << (i * 2)))
  //     length++;
  IFDEF(CONFIG_MTRACE, record_pwrite(waddr, wmask, wdata););

  int aligned_addr = waddr & ~0x3u; // 对齐地址
  int offset = waddr & 0x3u;

  // printf("addr=%x off=%x data=%x\n",aligned_addr,offset,wdata);

  if (aligned_addr == 0xa00003f8)
  {
    printf("%c", wdata);
    fflush(stdout);
    // putchar((char)(wdata&wmask));
    return;
  }

  uint32_t current_data = mem[(aligned_addr - 0x80000000) / 4];
  uint32_t new_data = current_data;

  for (int i = 0; i + offset < 4; ++i)
  {
    if (wmask & (3 << (i * 2)))
    {
      ((uint8_t *)&new_data)[i + offset] = ((uint8_t *)&wdata)[i];
    }
  }
  // printf("addr=%x current_data=%x new_data=%x off=%x\n",aligned_addr,current_data,new_data,offset);
  mem[(aligned_addr - 0x80000000) / 4] = new_data;
}

uint32_t mem_read(uint32_t pc)
{
  if (pc == 0xa0000048)
  {
    time_now = get_time();
    // printf("%lx\n", time);
    return (uint32_t)time_now;
  }
  if (pc == 0xa000004c)
  {
    return (uint32_t)(time_now >> 32);
  }
  return mem[(pc - 0x80000000) / 4];
}

uint32_t warp_pmem_read(uint32_t addr)
{
  return mem_read(addr);
}
void init_mrom(char *img_file)
{
  int size = 0;
  FILE *fp = fopen(img_file, "rb");
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  fread(mrom, size, 1, fp);
  fclose(fp);
}

void init_flash(){
  for(int i=0;i<1000;i++){
    flash[i]=i;
  }
}

void init_img(char *img_file)
{
  init_mrom(img_file);
  init_flash();
  // size_t size = 0;
  if (img_file != NULL)
  {
    FILE *fp = fopen(img_file, "rb");
    // Assert(fp, "Can not open '%s'", img_file);
    fseek(fp, 0, SEEK_END);
    mem_size = ftell(fp);
    // Log("The image is %s, size = %ld", img_file, size);
    Log("The image is %s, size = %d", img_file, mem_size);
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