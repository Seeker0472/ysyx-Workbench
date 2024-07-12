#include <common.h>
#include <debug.h>

void dtrace_read(const char * name,paddr_t addr,int len){
    Log("READ device %s at 0x%x len=%d",name,addr,len);
}

void dtrace_write(const char * name,paddr_t addr,int len,word_t data){
    Log("WRITE device %s at 0x%x len=%d data=0x%x",name,addr,len,data);
}