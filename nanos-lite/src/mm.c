#include <memory.h>
#include <stdlib.h>

static void *pf = NULL;
// execve calls new_page!!
// execve 不会 反回原来的控制流，而是在原来的地方创建！
void *new_page(size_t nr_page) {
  // size_t page_size = nr_page*PGSIZE;
  // return malloc(page_size);
  void *pf_prev = pf;
  pf_prev+=nr_page*PGSIZE;
  return pf_prev;
}

#ifdef HAS_VME
static void *pg_alloc(int n) {
  void *page_prev = pf;
  pf+=PGSIZE;
  return page_prev;
}
#endif

void free_page(void *p) {
  panic("not implement yet");
}

/* The brk() system call handler. */
int mm_brk(uintptr_t brk) {
  return 0;
}
// THE Kernel should also run in vitural memory,but the pa==va!!
void init_mm() {
  pf = (void *)ROUNDUP(heap.start, PGSIZE);//TODO:print %p
  Log("free physical pages starting from %x", pf);

#ifdef HAS_VME
  vme_init(pg_alloc, free_page);
#endif
}
