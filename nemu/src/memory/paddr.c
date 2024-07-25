/***************************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include <memory/host.h>
#include <memory/paddr.h>
#include <device/mmio.h>
#include <isa.h>

// my-func
void record_pread(paddr_t addr, int len);
void record_pwrite(paddr_t addr, int len, word_t data);

#if defined(CONFIG_PMEM_MALLOC)
static uint8_t *pmem = NULL;
#else // CONFIG_PMEM_GARRAY
static uint8_t pmem[CONFIG_MSIZE] PG_ALIGN = {};
static uint8_t sram[0x10000000] PG_ALIGN = {};
static uint8_t mrom[0x2000] PG_ALIGN = {};
#endif

uint8_t *guest_to_host(paddr_t paddr)
{
  if (paddr >= 0x20000000 && paddr <= 0x20000fff) // mrom
    return mrom + paddr - 0x20000000;
  if (paddr >= 0x0f000000 && paddr <= 0x0fffffff) // sram
    return sram + paddr - 0x0f000000;
  return pmem + paddr - CONFIG_MBASE;
}
paddr_t host_to_guest(uint8_t *haddr)
{
  if (haddr - mrom + 0x20000000 >= 0x20000000 && haddr - mrom + 0x20000000 <= 0x20000fff) // mrom
    return haddr - mrom + 0x20000000;
  if (haddr - sram + 0x0f000000 >= 0x0f000000 && haddr - sram + 0x0f000000 <= 0x0fffffff) // sram
    return haddr - sram + 0x0f000000;
  return haddr - pmem + CONFIG_MBASE;
}

static word_t pmem_read(paddr_t addr, int len)
{
  word_t ret = host_read(guest_to_host(addr), len);
  return ret;
}
// my-func
word_t warp_pmem_read(paddr_t addr)
{
  uint8_t *trans = pmem + (addr - CONFIG_MBASE);
  return *(uint32_t *)trans;
}

static void pmem_write(paddr_t addr, int len, word_t data)
{
  host_write(guest_to_host(addr), len, data);
}

static void out_of_bound(paddr_t addr)
{
  panic("address = " FMT_PADDR " is out of bound of pmem [" FMT_PADDR ", " FMT_PADDR "] at pc = " FMT_WORD,
        addr, PMEM_LEFT, PMEM_RIGHT, cpu.pc);
}

void init_mem()
{
#if defined(CONFIG_PMEM_MALLOC)
  pmem = malloc(CONFIG_MSIZE);
  assert(pmem);
#endif
  IFDEF(CONFIG_MEM_RANDOM, memset(pmem, rand(), CONFIG_MSIZE));
  Log("physical memory area [" FMT_PADDR ", " FMT_PADDR "]", PMEM_LEFT, PMEM_RIGHT);
}

// paddr_read()和paddr_write()会判断地址addr落在物理内存空间还是设备空间, 若落在物理内存空间, 就会通过pmem_read()和pmem_write()来访问真正的物理内存; 否则就通过map_read()和map_write()来访问相应的设备.
word_t paddr_read(paddr_t addr, int len)
{
  IFDEF(CONFIG_MTRACE, record_pread(addr, len);)
  if (likely(in_pmem(addr)))
    return pmem_read(addr, len);
  IFDEF(CONFIG_DEVICE, return mmio_read(addr, len));
  out_of_bound(addr);
  return 0;
}

void paddr_write(paddr_t addr, int len, word_t data)
{
  IFDEF(CONFIG_MTRACE, record_pwrite(addr, len, data);)
  if (likely(in_pmem(addr)))
  {
    pmem_write(addr, len, data);
    return;
  }
  IFDEF(CONFIG_DEVICE, mmio_write(addr, len, data); return);
  out_of_bound(addr);
}
