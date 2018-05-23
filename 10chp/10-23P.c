//#include "apue.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

volatile sig_atomic_t quitflag;

static void sig_int(int signo){
  if(signo == SIGINT)
    printf("\ninterrupt\n");
  else if(signo == SIGQUIT)
    quitflag = 1;
}

int main(int argc,char *argv[]){
  sigset_t newmask,oldmask,zeromask;
  quitflag = 0;

  if(signal(SIGINT,sig_int) == SIG_ERR)
    printf("signal(SIGINT) err");
  if(signal(SIGQUIT,sig_int) == SIG_ERR)
    printf("signal(SIGQUIT) err");


  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGQUIT);

  if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
    printf("SIG_BLOCK err");
  while(quitflag == 0)
    sigsuspend(&zeromask);

  printf("\nout while\n");

  quitflag = 0;
  if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
    printf("SIG_SETMASK err");

  exit(0);
}
