#include "kernel/param.h"
#include "kernel/types.h"
#include "user/printf.c"
#include "user/user.h"

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
  int priority[NPROC];

  for(n=0; n<N; n++){
    pid = fork(n % 4);
    if(pid == 0) {
      waste_time();
      exit(0);
    }
    else {
      printf("started child %d with priority %d\n", pid, n % 4);
      child[n] = pid;
      priority[pid] = n % 4;
    }
  }

  for(n=0; n<N; n++){
    pid = wait(0);
    printf("Child pid = %d finished with priority %d!\n", pid, priority[pid]);
  }

  exit(0);
}