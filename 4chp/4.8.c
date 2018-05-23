#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc,char *argv[]){
  umask(0);
  if(creat("foo",RWRWRW) < 0)
    err_sys("creat error foo");
  umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  if(creat("bar",RWRWRW) < 0)
    err_sys("creat err_sys bar");
  exit(0);
}
