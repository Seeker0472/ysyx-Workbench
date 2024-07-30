#include "trap.h"

uint32_t * data = (uint32_t *)0x30000000L;

int main(){
    // for(int i=1;i<1000;i++)
    //     check(data[i]==i);    
    for(int i=1;i<100;i++)
        printf("%x\n",data[i]);
}