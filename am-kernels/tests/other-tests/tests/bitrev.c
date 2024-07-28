#include "am.h"
#include "trap.h"
#include "soc.h"

#define SPI_MASTER 0x10001000L

void init_bit_rev(){
    outl(SPI_MASTER +0x14,0x02);
}
void send_data(){
    outl(SPI_MASTER + 0x18,0x7);//ss reg
    // outl(SPI_MASTER + 0x10,0x140f);//ctrl reg
    outl(SPI_MASTER,0x1);
    outl(SPI_MASTER + 0x10,0x148f);//start

}
void wait_data(){
    while(inl(SPI_MASTER+0x10)&0x80)
        continue;
    inl(SPI_MASTER);
}
int main(){
    init_bit_rev();
    send_data();
    wait_data();
    return 0;
}