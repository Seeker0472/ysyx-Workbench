#include <stdio.h>
int main(void)
{
  // printf("Hello!!!!!!!!!!!!!!!!!!!!!!!!\n");
  printf("Hello!!!!!!!!!!!!!!!!!!!!!!!!\n");

  for(volatile int i=0;i<100;i++);
  printf("Hello!!!!!!!!!!!!!!!!!!!!!!!!\n");
  for(volatile int i=0;i<100;i++);


  printf("Hello!!!!!!!!!!!!!!!!!!!!!!!!\n");
  for(volatile int i=0;i<100;i++);

  printf("Hello!!!!!!!!!!!!!!!!!!!!!!!!\n");
  for(volatile int i=0;i<100;i++);


  printf("Hello!!!!!!!!!!!!!!!!!!!!!!!!\n");



  return 0;
}
