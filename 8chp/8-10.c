#include "apue.h"
#include <sys/wait.h>

char *env_init[]={"USER=unknown","PATH=/tmp",NULL};

int main(int argc,char *argv[]){
  pid_t pid;

  if((pid = fork()) < 0){
    err_sys("fork err");
  }
  else if(pid == 0){
    if(execle("/home/sar/bin/echoall","echoall","myarg1",
          "MY ARG2",(char *)0,env_init) < 0)
      err_sys("execle err");
  }
  if(waitpid(pid,NULL,0) < 0)
    err_sys("wait err");

  if((pid = fork()) < 0){
    err_sys("fork error");
  }
  else if(pid == 0){
    if(execlp("echoall","echoall","only 1 arg",(char *)0) < 0)
      err_sys("execlp err");
  }
  
  exit(0);
}