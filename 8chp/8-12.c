#include "apue.h"
#include <sys/wait.h>

int main(int argc,char *argv[]){
  pid_t pid;
  if((pid = fork()) < 0)
    err_sys("fork error");
  else if(pid == 0){
    if(execl("/home/hanxu/bin/ls.sh","ls.sh","-al",(char *)0) < 0)
      err_sys("execl err");
  }
  if(waitpid(pid,NULL,0) < 0)
    err_sys("waitpid err");

  exit(0);
}
