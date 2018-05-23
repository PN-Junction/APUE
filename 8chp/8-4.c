//#include "apue.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int globvar=6;

int main(int argc,char *argv[]){
  int var;
  pid_t pid;

  var=88;
  printf("before vfork\n");

  if((pid=vfork()) < 0){
    printf("fork error");
  }
  else if(pid == 0){
    globvar++;
    var++;
    _exit(0);
  }
//  else{
//    sleep(2);
//  }
  printf("pid=%ld,glob=%d,var=%d\n",(long)getpid(),globvar,var);
  exit(0);
}
