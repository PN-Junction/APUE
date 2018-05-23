#include "apue.h"

static void sig_int(int signo){
  printf("caught SIGINT\n");
}

static void sig_chld(int signo){
  printf("caught SIGCHLD\n");
}

int main(void){
  if(signal(SIGINT,sig_int) == SIG_ERR)
    printf("signal(SIGINT) err");
  if(signal(SIGCHLD,sig_chld) == SIG_ERR)
    printf("signal(SIGCHLD) err");
  if(system("/bin/ed") < 0)
    printf("system() err");


  exit(0);
}
