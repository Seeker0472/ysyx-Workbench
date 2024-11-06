#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>

int main() {
  printf("Hello for every 0.5 sec");
  int i = 0;
  uint64_t time_us;
  uint64_t prev_time_us=0;
  struct timeval stime;
  while (1) {
    gettimeofday(&stime, NULL);
    time_us=stime.tv_sec*1000000+stime.tv_usec;
    if (time_us-prev_time_us>500000) {
      printf("Hello World from Navy-apps for the %dth time!\n", i++);
      prev_time_us=time_us;
    }
  }
  return 0;
}
