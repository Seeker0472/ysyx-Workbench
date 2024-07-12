#include <stdio.h>
int main(void)
{
  {
    int y=21312332,x=1;
    printf("success %d str===%s\n",4432,"1243");

      printf("line %d: %s: %d  %s  %d  ==  %d =>  %s (%d)\n", __LINE__, "signed int", 0x80000000, "+", 0x80000000, 0x0, (signed int)(x + y) == 0x0 ? "PASS" : "FAIL", (signed int)(x + y));
      printf("line :\n");
  }
  return 0;
}
