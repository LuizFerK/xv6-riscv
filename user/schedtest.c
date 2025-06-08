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
  int p_tickets;
  int n, pid;
  int tickets[NPROC];

  for(n=0; n<N; n++){
    p_tickets = N * 100 - n * 100;
    pid = fork(p_tickets);
    if(pid == 0) {
      waste_time();
      exit(0);
    }
    else {
      printf("started child %d with %d tickets\n", pid, p_tickets);
      child[n] = pid;
      tickets[pid] = p_tickets;
    }
  }

  for(n=0; n<N; n++){
    pid = wait(0);
    printf("Child pid = %d finished with %d tickets!\n", pid, tickets[pid]);
  }

  exit(0);
}