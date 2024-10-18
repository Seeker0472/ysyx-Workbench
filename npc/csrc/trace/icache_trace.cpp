#include "common.h"
#include "debug.h"
#include "macro.h"
typedef struct {
  paddr_t addr;
  word_t inst;
} icache_Node;
#define BUF_SIZE 50
icache_Node ibuf[BUF_SIZE];
int ptail = 0;
bool full= false;
word_t find_inst(vaddr_t addr) {
  if (likely(full)) {
    for (int i = 0; i < BUF_SIZE - 1; i++) {
      if (ibuf[i].addr == addr)
        return ibuf[i].inst;
    }
  } else {
    for (int i = 0; i < ptail; i++) {
      if (ibuf[i].addr == addr)
        return ibuf[i].inst;
    }
  }
  Assert(0, "Should NOT reach here!!");
}
void insert_icache_result(paddr_t addr, word_t inst) {
  ibuf[ptail].addr = addr;
  ibuf[ptail].inst = inst;
  if (unlikely(!full && ptail == BUF_SIZE - 1))
    full=true;
  ptail=(ptail+1)%BUF_SIZE;
}