#include"trap.h"
int main(){
    char temp[999];
    for(int i=0;i<1000;i++){
        int len=rand()%99;
        for(int i=0;i<len;i++)
            temp[i]=rand()%20+65;
        temp[len]='\0';
        assert(strlen(temp)==len);
    }
}