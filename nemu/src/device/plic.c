#include <device/map.h>

static uint32_t *base = NULL;
/* TODO: not imp yet */
static void plic_io_handler(uint32_t offset, int len, bool is_write) {
  Log("MMIO_DEV(%s) on %x,%x",is_write?"write":"read",offset,len);
}


void init_plic() {
   base = (uint32_t *)new_space(CONFIG_PLIC_MEM_SIZE);
  add_mmio_map("sdhci", CONFIG_PLIC_MEM_SIZE, base, CONFIG_PLIC_MEM_SIZE, plic_io_handler);
}

