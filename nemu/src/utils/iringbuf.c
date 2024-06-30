#include <common.h>

typedef struct
{
    paddr_t pc;
    word_t inst;
} inst_Node;

#define BUF_SIZE 20

inst_Node ibuf[BUF_SIZE];
char logbuf[128];
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
    char *p=logbuf;
    p += snprintf(p, sizeof(logbuf), FMT_WORD ": ", (vaddr_t)pc);//打印地址
    int ilen=4;//TODO:HOW?
    //打印接下的东西
    #ifndef CONFIG_ISA_loongarch32r
    void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
    disassemble(p, logbuf + sizeof(logbuf) - p,
        pc, (uint8_t *)&inst, ilen);//反
    #else
    p[0] = '\0'; // the upstream llvm does not support loongarch32r
    #endif
    //TODO:print logbuf!!!!!!!
    while(*p!='\0')
        p++;
    memset(p, ' ',p-logbuf+40);
    fprintf(stdout,"%s\n",logbuf);
    puts(logbuf);
    // printf("%x   %lx\n",pc,inst);
}

void print_iringbuf(){
    Log("Recentl Instr");
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

