#include "apue.h"
#include <errno.h>

static void sig_hup(int signo){
  printf("SIGHUP received ,pid = %ld\n",(long)getpid());
}
static void sig_int(int signo){
  printf("SIGINT received ,pid = %ld\n",(long)getpid());
}

static void pr_ids(char *name){
  printf("%s:pid = %ld,ppid = %ld,pgrp = %ld,tpgrp = %ld\n",
      name,(long)getpid(),(long)getppid(),(long)getpgrp(),
      (long)tcgetpgrp(STDIN_FILENO));
  fflush(stdout);
}

int main(void){
  char c[10];
  char a;
  pid_t pid;
  pid_t sid;

  pr_ids("parent");
  if((pid = fork()) < 0){
    err_sys("fork error");
  }
  else if(pid > 0){
    sleep(2);
  }
  else{
    pr_ids("child");
    signal(SIGHUP,sig_hup);
    signal(SIGINT,sig_int);
    kill(getpid(),SIGTSTP);
    sid = setsid();
    if(sid < 0)
      err_sys("set sid err\n");
    pr_ids("child");
    sleep(5);
    if(read(STDIN_FILENO,c,9) < 0)
      printf("read error %d on controlling TTY\n",errno);
    else
      printf("I get %s\n",c);
  }
  exit(0);
}
