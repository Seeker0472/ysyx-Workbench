#include "common.h"
#include "debug.h"
#include "macro.h"
typedef struct {
  paddr_t addr;
  word_t inst;
} icache_Node;
#define BUF_SIZE 10
icache_Node itbuf[BUF_SIZE];
int ptail = 0;
bool full= false;
word_t find_inst(vaddr_t addr) {
  if (likely(full)) {
    for (int i = 0; i < BUF_SIZE - 1; i++) {
      if (itbuf[i].addr == addr)
        return itbuf[i].inst;
    }
  } else {
    for (int i = 0; i < ptail; i++) {
      if (itbuf[i].addr == addr)
        return itbuf[i].inst;
    }
  }
//   Log("Should NOT reach here!!");
  return 0;
}
void insert_icache_result(paddr_t addr, word_t inst) {
  itbuf[ptail].addr = addr;
  itbuf[ptail].inst = inst;
  if (unlikely(!full && ptail == BUF_SIZE - 1))
    full=true;
  ptail=(ptail+1)%BUF_SIZE;
}