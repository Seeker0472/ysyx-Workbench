#include "trap.h"

uint32_t * data = (uint32_t *)0x30000000L;

int main(){
    for(int i=0;i<1000;i++)
        check(data[i]==i);
}