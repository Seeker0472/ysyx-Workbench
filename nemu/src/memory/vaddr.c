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
#include <memory/paddr.h>

// TODO-TYPE
// TODO: Finish

word_t vaddr_ifetch(vaddr_t addr, int len) {
  paddr_t paddr=addr;
  switch (isa_mmu_check(paddr, len, 0)) {
  case MMU_DIRECT:
    break;
  case MMU_TRANSLATE:
    paddr = isa_mmu_translate(addr,len,0);
    break;
  case MMU_FAIL:
    assert(0);
    break;
  }
  assert(paddr != MEM_RET_CROSS_PAGE);
  assert(paddr != MEM_RET_FAIL);
  return paddr_read(paddr, len);
}

word_t vaddr_read(vaddr_t addr, int len) {
  // return paddr_read(addr, len);
  paddr_t paddr=addr;
  switch (isa_mmu_check(paddr, len, 0)) {
  case MMU_DIRECT:
    break;
  case MMU_TRANSLATE:
    paddr = isa_mmu_translate(addr,len,0);
    break;
  case MMU_FAIL:
    assert(0);
    break;
  }
  assert(paddr != MEM_RET_CROSS_PAGE );
  assert(paddr != MEM_RET_FAIL);
  return paddr_read(paddr, len);
}

void vaddr_write(vaddr_t addr, int len, word_t data) {
  // paddr_write(addr, len, data);
  paddr_t paddr=addr;
  switch (isa_mmu_check(paddr, len, 0)) {
  case MMU_DIRECT:
    break;
  case MMU_TRANSLATE:
    paddr = isa_mmu_translate(addr,len,0);
    break;
  case MMU_FAIL:
    assert(0);
    break;
  }
  assert(paddr != MEM_RET_CROSS_PAGE);
  assert(paddr != MEM_RET_FAIL);
  paddr_write(paddr, len,data);
}
