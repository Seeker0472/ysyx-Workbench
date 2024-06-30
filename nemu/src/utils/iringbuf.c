#include <common.h>

typedef struct
{
    paddr_t pc;
    word_t inst;
} inst_Node;

#define BUF_SIZE 20

inst_Node ibuf[BUF_SIZE];

int pbuf=0;
bool full=false;

void write_iringbuf(paddr_t pc, word_t inst){
    ibuf[pbuf].pc=pc;
    ibuf[pbuf].inst=inst;
    if(pbuf==BUF_SIZE-1)
        full=true;
    pbuf=(pbuf+1)%BUF_SIZE;
}

void print_iringbuf(){
    printf("TODO:iring buff");
}