#include "../include/ydb_all.h"
#include <stdint.h>
#include <stdio.h>

void record_pread(paddr_t addr, int len);
void record_pwrite(paddr_t addr, char wmask, word_t data);
uint32_t mem_read(uint32_t pc);
extern uint32_t *mrom;
extern uint32_t *flash;
extern uint32_t *mem;
extern uint32_t *psram;
extern uint64_t time_now;
// DPI-C Funcs
extern "C" void flash_read(int32_t addr, int32_t *data) {
  // printf("%x---%x\n",addr,flash[addr/4]);
  *data = flash[addr / 4];
}
extern "C" void mrom_read(int32_t addr, int32_t *data) {
  *data = mrom[(addr - 0x20000000) / 4];
}

extern "C" void psram_read(int32_t addr, int32_t *data) {
  *data = psram[(addr - 0x80000000) / 4];
}
extern "C" void psram_write(int32_t addr, int32_t data) {
  printf("addr=%x,data=%x\n",addr,data);
  psram[(addr - 0x80000000) / 4] = data;
}

extern "C" int get_time(int raddr) {
  if (raddr == 0x10000048) {
    time_now = get_time();
    return (uint32_t)time_now;
  }
  if (raddr == 0x1000004c) {
    return (uint32_t)(time_now >> 32);
  }
  return -1;
}

extern "C" int pmem_read(int raddr) {
  // 总是读取地址为`raddr & ~0x3u`的4字节返回
  // Log("mem_read");
  int aligned_addr = raddr & ~0x3u; // 对齐地址
  IFDEF(CONFIG_MTRACE, record_pread(raddr, 4););

  return mem_read(aligned_addr);
}
extern "C" void pmem_write(int waddr, int wdata, char wmask) {
  // 总是往地址为`waddr & ~0x3u`的4字节按写掩码`wmask`写入`wdata`
  // `wmask`中每比特表示`wdata`中1个字节的掩码,
  // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
  IFDEF(CONFIG_MTRACE, record_pwrite(waddr, wmask, wdata););

  int aligned_addr = waddr & ~0x3u; // 对齐地址
  int offset = waddr & 0x3u;

  if (aligned_addr == 0xa00003f8) {
    printf("%c", wdata);
    fflush(stdout);
    // putchar((char)(wdata&wmask));
    return;
  }

  uint32_t current_data = mem[(aligned_addr - 0x80000000) / 4];
  uint32_t new_data = current_data;

  for (int i = 0; i + offset < 4; ++i) {
    if (wmask & (3 << (i * 2))) {
      ((uint8_t *)&new_data)[i + offset] = ((uint8_t *)&wdata)[i];
    }
  }
  mem[(aligned_addr - 0x80000000) / 4] = new_data;
}