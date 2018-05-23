#include "apue.h"
#include <fcntl.h>

#define BUF_SIZE 1024

char rbuf[BUF_SIZE]={0};
char wbuf[BUF_SIZE]={0};
int wptr;

int main(int argc,char *argv[]){
  int fd,fd2;
  int n,i;
  char tmp;
  struct stat sbuf,sbufcpy;
  struct timespec times[2];
  char *cpy;
  if(lstat(argv[1],&sbuf) < 0)
    err_ret("lstat %s error",argv[1]);
  if((fd = open(argv[1],O_RDONLY)) < 0)
    err_sys("open %s failed:",argv[1]);
  sprintf(cpy,"%s.CP",argv[1]);
  if((fd2 = creat(cpy,O_WRONLY)) < 0)
    err_sys("creat %s failed:",argv[1]);

  while((n = read(fd,rbuf,BUF_SIZE)) > 0){
    //printf("rbuf OK size %d \n",n);
    wptr = 0;
    for(i=0;i<n;i++){
      if(rbuf[i] != 0){
        wbuf[wptr] = rbuf[i];
        wptr++;
      }
    }
    //printf("\nwbuf OK wptr:%d\n",wptr);
    if((write(fd2,wbuf,wptr)) != wptr)
      err_sys("write %s failed",cpy);
  }
  if(fchmod(fd2,sbuf.st_mode) != 0)
    err_sys("chmod failed");
  if(fchown(fd2,-1,-1) != 0)
    err_sys("chown failed");
  times[0] = sbuf.st_atim;
  times[1] = sbuf.st_mtim;
  if(futimens(fd2,times) != 0)
    err_sys("change time failed");

  //if(lstat(cpy,&sbufcpy) < 0)
  //  err_ret("lstat %s error",cpy);
  //sbufcpy = sbuf;
  
  exit(0);
}
