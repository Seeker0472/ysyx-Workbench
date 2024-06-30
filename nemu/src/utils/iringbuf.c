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

void print_isnt(paddr_t pc, word_t inst){
    printf("%x   %lx\n",pc,inst);
}

void print_iringbuf(){
    if(full){
        for(int i=(pbuf+1)%BUF_SIZE;i!=pbuf;i=(i+1)%BUF_SIZE){
            print_isnt(ibuf[i].pc,ibuf[i].inst);
        }
    }else{
        for(int i=0;i!=pbuf;i++){
            print_isnt(ibuf[i].pc,ibuf[i].inst);
        }
    }
}

