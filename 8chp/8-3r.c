#include "apue.h"
#include <sys/wait.h>


int main(int argc,char *argv[]){
  pid_t pid;
  siginfo_t infop;
  int status;

  if((pid=fork()) < 0)
    err_sys("fork err");
  else if(pid == 0)
    exit(7);

  if(waitid(P_PID,pid,&infop,WEXITED) < 0)
//  if(wait(&status) != pid)
    err_sys("wait error");
  printf("exit errno: %d\n",infop.si_errno);
  printf("exit signo: %d\n",infop.si_signo);
  printf("exit status: %d\n",infop.si_status);
  printf("exit code: %d\n",infop.si_code);

  if((pid=fork()) < 0)
    err_sys("wait err");
  else if(pid == 0)
    abort();

  if(waitid(P_PID,pid,&infop,WEXITED) < 0)
//  if(wait(&status) != pid)
    err_sys("wait err");
  printf("exit errno: %d\n",infop.si_errno);
  printf("exit signo: %d\n",infop.si_signo);
  printf("exit status: %d\n",infop.si_status);
  printf("exit code: %d\n",infop.si_code);

  if((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid == 0)
    status /= 0;

  if(waitid(P_PID,pid,&infop,WEXITED) < 0)
//  if(wait(&status) != pid)
    err_sys("wait err");
  printf("exit errno: %d\n",infop.si_errno);
  printf("exit signo: %d\n",infop.si_signo);
  printf("exit status: %d\n",infop.si_status);
  printf("exit code: %d\n",infop.si_code);

  exit(0);
}
