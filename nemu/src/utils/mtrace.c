#include <common.h>

void record_pread(paddr_t addr, int len){
    Info("ReadAddr at: 0x%x len:%d\n",addr,len);
}

void record_pwrite(paddr_t addr, int len, word_t data){
    printf("WriteAddr at: 0x%x len:%d 0x%lx\n",addr,len,data);
}