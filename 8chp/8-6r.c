#include "apue.h"
#include <sys/wait.h>

int main(int argc,char *argv[]){
  pid_t pid;
  int status;

  if((pid = fork()) < 0)
    err_sys("fork err");
  else if(pid == 0)
    exit(0);

  sleep(1);
  if((status = system("ps -s")) < 0)
    err_sys("fork err");
}
