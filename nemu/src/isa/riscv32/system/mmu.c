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

#include "common.h"
#include <isa.h>
#include <memory/vaddr.h>
#include <memory/paddr.h>
#include <stdint.h>

#define PAGE(x) ((x) << 12) //get page addr
#define PTEM(x) (((uint32_t)(x)) & 0xFFFFFC00)
#define PAGE_VALID(x) ((x) & 0x1)
#define XWR(x) (((x) >> 1) & 0b111)


// page table walk
// pta page table address
// pte page table entry
// ptea page table entry address
// vpn virtual page number
// 对内存区间为[vaddr, vaddr + len), 类型为type的内存访问进行地址转换
// TODO:使用assertion检查页目录项和页表项的present/valid位, 如果发现了一个无效的表项, 及时终止NEMU的运行999
paddr_t isa_mmu_translate(vaddr_t vaddr, int len, int type) {
  // extract addr
  // Log("Vaddr:%x,len:%x",vaddr,len);
  vaddr_t pta1 = PAGE(cpu.csr[6] & 0x3FFFFF); // get root_page_table_addr
  vaddr_t vpn1 = vaddr >> 22;
  vaddr_t vpn0 = (vaddr >> 12) & 0x3FF;
  vaddr_t offset = vaddr & 0xFFF;

  // do page_walk
  uint32_t *ptea1 = (uint32_t*)guest_to_host(pta1 + vpn1*sizeof(uint32_t));//TODO:NOT DEFRENCE ONLY!
  uint32_t pte1 = *ptea1;
  vaddr_t pta0 = (PTEM(pte1)<<2);
  uint32_t *ptea0 = (uint32_t *)guest_to_host(pta0 + vpn0*sizeof(uint32_t));
  uint32_t pte0 = *ptea0;
  //final page address
  vaddr_t pa = (PTEM(pte0)<<2) | offset;

  // check address
  // not valid!
  // if (!(PAGE_VALID(pte0) && PAGE_VALID(pte1))) {
  //   Log("UNVALID:%x,%x,%x",vaddr,PAGE_VALID(pte0),PAGE_VALID(pte1));
  //   return MEM_RET_FAIL;
  // }
  // check RWX (TODO)
  // check U (TODO)
  // G&A&D don't care!

  // check bounds
  if (offset + len > 0x1000) {
    return MEM_RET_CROSS_PAGE;
  }
  // Log("Translate_result:%x-%x",vaddr,pa);
  return pa;

  // | ppn1 | ppn0 | offset
}
// Translate/direct/fail!
/*
TODO:is this okey?
The NEMU Address Table:
disk: 0x80000000-???
programs:0x83000000-disk.end<-translate
device:0xa0000000
*/
// 检查当前系统状态下对内存区间为[vaddr, vaddr + len), 类型为type的访问是否需要经过地址转换.
int isa_mmu_check(vaddr_t vaddr, int len, int type) {
  vaddr_t translate= cpu.csr[6]>>31; //enable sv32
  // vaddr_t end = vaddr+len;
  // if (vaddr > 0x80000000 && vaddr < 0xa0000000&&translate) {
  //   if(end > 0x80000000 && end < 0xa0000000)
  //     return MMU_TRANSLATE;
  //   else
  //     return MMU_FAIL;
  // }
  // else
  //   return MMU_DIRECT;
  if (translate)
    return MMU_TRANSLATE;
  else
   return MMU_DIRECT;;
}
