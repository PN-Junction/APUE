#include "apue.h"
#include <fcntl.h>

int main(int argc,char *argv[]){
    int i,fd;
    char n;
    char buf[10]={0};
    struct stat statbuf;
    struct timespec times[2];

    for(i=1;i<argc;i++){
      if(stat(argv[i],&statbuf) < 0){
        err_ret("%s:stat error",argv[i]);
        continue;
      }
      if((fd = open(argv[i],O_RDONLY)) < 0){
//      if((fd = open(argv[i],O_RDONLY|O_TRUNC)) < 0){
        err_ret("%s:open error",argv[i]);
        continue;
      }
      else{
        if((n = read(fd,buf,5)) < 0){
          err_ret("%s:read error",argv[i]);
          continue;
        }
        else
          printf("I get :%s",buf);
      }
      times[0] = statbuf.st_atim;
      times[1] = statbuf.st_mtim;
      if(futimens(fd,times) < 0)
        err_ret("%s:futimens error",argv[i]);
      close(fd);
    }
    exit(0);
}
