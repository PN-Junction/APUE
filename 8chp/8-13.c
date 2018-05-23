#include "apue.h"
#include <sys/wait.h>

void pr_exit(int status){
  if(WIFEXITED(status))
    printf("normal termination,exit status=%d\n",
        WEXITSTATUS(status));
  else if(WIFSIGNALED(status))
    printf("abnormal termination,exit status=%d%s\n",
        WTERMSIG(status),
#ifdef WCOREDUMP
        WCOREDUMP(status)?"(core file gen)":"");
#else
        "");
#endif
  else if(WIFSTOPPED(status))
    printf("child stopped,signal number = %d\n",
        WSTOPSIG(status));
}

int main(int argc,char *argv[]){
  int status;
  if((status = system("date")) < 0)
    err_sys("system err");

  pr_exit(status);

  if((status = system("nosuchcommand")) < 0)
    err_sys("system err");
  pr_exit(status);

  if((status = system("who;exit 44")) < 0)
    err_sys("system err");
  pr_exit(status);

  exit(0);
}



