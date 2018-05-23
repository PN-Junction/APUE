#include "apue.h"
#include <time.h>

#define TMBF_SIZE  64

int main(int argc,char *argv[]){
  time_t t;
  struct tm tmptr;
  char buf[TMBF_SIZE];

  if(time(&t) < 0)
    err_sys("time failed");
  tmptr = *localtime(&t);
  
  if(strftime(buf,TMBF_SIZE -1,
        "%a %b %e %T %Z %Y",&tmptr) < 0)
    err_sys("strftime failed");

  printf("%s\n",buf);
}
