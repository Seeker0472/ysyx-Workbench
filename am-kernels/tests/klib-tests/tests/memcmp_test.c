
#include"trap.h"
#define SIZE 10000

char mem[SIZE];

void initmem(){
    for(int i=0;i<SIZE;i++)
        mem[i]=i%200;
}

void write_mem(int start,int dstart,int len){
    for(int i=0;i<len;i++){
        mem[start+i]=mem[dstart+i]=rand()%20+65;
    }
    // mem[start+len]=mem[dstart+len]='\0';
}
bool a_ok(int start,int dstart,int len){
    if(start+len>=dstart-2)
        return false;
    if(dstart+len>=SIZE-2)
        return false;
    return true;
}
void check_once(){
    int start=rand()%(SIZE/2);
    int dstart=rand()%(SIZE/2)+(SIZE/2);
    int len=rand()%(SIZE/3)+1;
    if(a_ok(start,dstart,len)){
        // memcpy(mem+dstart,mem+start,len);
        write_mem(start,dstart,len);
        assert(!memcmp(mem+start,mem+dstart,len));
    }

}
int main(){
    initmem();
    // srand(time(0));
    for(int i=0;i<1000;i++){
        check_once();
    }
    return 0;
}