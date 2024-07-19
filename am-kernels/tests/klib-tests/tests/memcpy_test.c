
#include"trap.h"
#define SIZE 10000

char mem[SIZE];

void initmem(){
    for(int i=0;i<SIZE;i++)
        mem[i]=i%200;
}

void check_mem(int start,int dstart,int len){
    for(int i=0;i<len-2;i++){
        // putch(len+'0');
        // putch((mem[start+i]!=mem[dstart+i])+'0');
        // putch((mem[start+i])+'0');
        // putch((mem[dstart+i])+'0');
        // putch('\n');
        assert(mem[start+i]==mem[dstart+i]);

    }
    
}
bool a_ok(int start,int dstart,int len){
    if(start+len>=dstart-1)
        return false;
    if(dstart+len>=SIZE-1)
        return false;

    return true;
}
void check_once(){
    int start=rand()%(SIZE/2);
    int dstart=rand()%(SIZE/2)+(SIZE/2);
    int len=rand()%(SIZE/3)+1;
    // int start=2075;
    // int dstart=5975;
    // int len=4;
    if(a_ok(start,dstart,len)){
        // putch('L');
        // putch(dstart/1000+'0');
        // putch((dstart%1000)/100+'0');
        // putch((dstart%100)/10+'0');
        // putch((dstart%10+'0'));
        // putch('\n');

        memcpy(mem+dstart,mem+start,len);
        check_mem(start,dstart,len);
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