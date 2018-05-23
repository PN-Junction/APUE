#include "apue.h"
#include <sys/utsname.h>

int main(int argc,char *argv[]){
  struct utsname name;
  if(uname(&name) < 0)
    err_sys("uname failed");

  printf("%s\t",name.sysname);
  printf("%s\t",name.nodename);
  printf("%s\t",name.release);
  printf("%s\t",name.version);
  printf("%s\n",name.machine);
}
