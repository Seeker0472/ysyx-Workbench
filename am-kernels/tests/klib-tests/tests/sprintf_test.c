#include"trap.h"
#include<limits.h>

int val[]={0, INT_MAX / 17, INT_MAX, INT_MIN, INT_MIN + 1,
              UINT_MAX / 17, INT_MAX / 17, UINT_MAX};
char* result[]={"0","126322567","2147483647","-2147483648","-2147483647","252645135","126322567","-1"};

int main(){
    char buffer[30];
    for(int i=0;i<8;i++){
        memset(buffer,0,30);
        sprintf(buffer,"%d",val[i]);
        assert(memcmp(buffer,result[i],30));
    }
    return 0;
}