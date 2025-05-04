#include "kernel/types.h"
#include "user/user.h"
#include "user/printf.c"

#define N  4

int child[N];

void waste_time(){
  volatile unsigned long long i;
  for (i = 0; i < 300000000ULL; ++i);
}

int
main(int argc, char *argv[])
{
  int n, pid;
  for(n=0; n<N; n++){
    pid = fork(n % 4);
    if(pid == 0) {
      waste_time();
      exit(0);
    }
    else {
      printf("started child %d\n", pid);
      child[n] = pid;
    }
  }

  for(n=0; n<N; n++){
    pid = wait(0);  
    printf("Child pid = %d finished!\n", pid);
  }

  exit(0);
}