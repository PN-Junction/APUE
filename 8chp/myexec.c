#include "apue.h"
#include <sys/wait.h>

int main(int argc,char *argv[]){
  pid_t pid;

  if((pid = fork()) < 0){
    err_sys("fork err");
  }
  else if(pid == 0){
//    if(execle("/home/sar/bin/echoall","echoall","myarg1",
//          "MY ARG2",(char *)0,env_init) < 0)
    if(execlp("ls.sh","ls.sh","-al"))
      err_sys("execle err");
  }
  if(waitpid(pid,NULL,0) < 0)
    err_sys("wait err");

  exit(0);
}
