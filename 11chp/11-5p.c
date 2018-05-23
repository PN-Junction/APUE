#include "apue.h"
#include <pthread.h>

void
cleanup(void *arg){
  printf("cleanup: %s\n",(char *)arg);
}

void *
thr_fn1(void *arg){
  printf("thread 1 start\n");
  pthread_cleanup_push(cleanup,"thread 1 first handler");
  pthread_cleanup_push(cleanup,"thread 1 second handler");
  printf()
}
