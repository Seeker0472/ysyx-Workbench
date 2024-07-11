#include <stdio.h>
#include <cstdint>
#include <debug.h>
#include <common.h>

void record_pread(paddr_t addr, int len);
void record_pwrite(paddr_t addr, int len, word_t data);
uint32_t mem[0x8000000] = {
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
word_t mem_size = 84;

uint32_t mem_read(uint32_t pc)
{
  // //mtrace
  // //TODO: Write  Enable-------------------------------------------------
  return mem[(pc - 0x80000000) / 4];
}

extern "C" int pmem_read(int raddr)
{
  // 总是读取地址为`raddr & ~0x3u`的4字节返回
  // Log("mem_read");
  int aligned_addr = raddr & ~0x3u; // 对齐地址
  record_pread(aligned_addr, 4);
  return mem_read(raddr);
}
extern "C" void pmem_write(int waddr, int wdata, char wmask)
{
  // 总是往地址为`waddr & ~0x3u`的4字节按写掩码`wmask`写入`wdata`
  // `wmask`中每比特表示`wdata`中1个字节的掩码,
  // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
  // Log("mem_write");
  int length = 0;
  for (int i = 0; i < 4; i++)
    if (wdata & (1 << (i*2)))
      length++;

  record_pwrite(waddr, length, wdata);
  int aligned_addr = waddr & ~0x3u; // 对齐地址
  uint32_t current_data = mem[(aligned_addr - 0x80000000) / 4];
  uint32_t new_data = current_data;

  for (int i = 0; i < 4; ++i)
  {
    if (wmask & (1 << i))
    {
      ((uint8_t *)&new_data)[i] = ((uint8_t *)&wdata)[i];
    }
  }
  mem[(aligned_addr - 0x80000000) / 4] = new_data;
}

uint32_t warp_pmem_read(uint32_t addr)
{
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