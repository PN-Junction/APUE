#include "apue.h"
#include <time.h>

#define _GET_CHAR_ 

int main(int argc,char *argv[]){
  clock_t start,end;
  double dur;

  int c;
  char buf[MAXLINE];

  start = clock();

#ifdef _GET_CHAR_
  while((c = getc(stdin)) != EOF)
    if(putc(c,stdout) == EOF)
      err_sys("putc err");

  if(ferror(stdin))
    err_sys("getc err");
#endif

#ifdef _GET_LINE_
  while((fgets(buf,MAXLINE,stdin)) != NULL)
    if(fputs(buf,stdout) == EOF)
      err_sys("puts err");

  if(ferror(stdin))
    err_sys("gets err");
#endif
  end = clock();

  dur = (double)(end - start)/CLOCKS_PER_SEC;

  printf("\n#dur is %f\n",dur);

  exit(0);
}
