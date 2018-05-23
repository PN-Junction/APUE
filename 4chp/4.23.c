#include "apue.h"

int main(int argc,char *argv[]){
  if(chdir("argv[1]") < 0)
    err_sys("chdir %s failed\n",argv[1]);
  else{
    printf("chdir %s succeeded\n",argv[1]);
  }
  exit(0);
}
