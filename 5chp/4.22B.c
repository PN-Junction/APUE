#include "apue.h"
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>

typedef int Myfunc(const char *,const struct stat *,int);

static Myfunc myfunc;
static int myftw(char *,Myfunc *);
static int dopath(Myfunc *);
static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;
//static char *path_alloc(int* size);
static char *pathalloc(size_t *size) {
  char *p = NULL;
  if(!size) return NULL;
  p = malloc(256);
  if(p)
    *size = 256;
  else
    *size = 0;
  return p;
}

int main(int argc,char *argv[]){
  int ret;
  clock_t start,finish;
  double dur;
  if(argc != 2)
    err_quit("usage: ftw <starting-pathname>");
  start = clock();
  ret = myftw(argv[1],myfunc);
  finish = clock();
  dur = (double)(finish - start)/CLOCKS_PER_SEC;
  printf("clocks per sec is %d\n",CLOCKS_PER_SEC);
  printf("start time is %d\n",start);
  printf("finish time is %d\n",finish);
  printf("total time is %f\n",dur);
  ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
  if(ntot == 0)
    ntot = 1;
  printf("regular files = %7ld,%5.2f %% \n",nreg,nreg*100.0/ntot);
  printf("directories = %7ld,%5.2f %% \n",ndir,ndir*100.0/ntot);
  printf("block special = %7ld,%5.2f %% \n",nblk,nblk*100.0/ntot);
  printf("char special = %7ld,%5.2f %% \n",nchr,nchr*100.0/ntot);
  printf("FIFOs = %7ld,%5.2f %% \n",nfifo,nfifo*100.0/ntot);
  printf("symbolic links = %7ld,%5.2f %% \n",nslink,nslink*100.0/ntot);
  printf("sockets = %7ld,%5.2f %% \n",nsock,nsock*100.0/ntot);

  exit(ret);
}


#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

static char *fullpath;
static char *filename;
static size_t pathlen;

static int myftw(char *pathname,Myfunc *func){
  fullpath = pathalloc(&pathlen);
  filename = malloc(sysconf(_PC_NAME_MAX));

  if(pathlen <= strlen(pathname)){
    pathlen = strlen(pathname) * 2;
    if((fullpath = realloc(fullpath,pathlen))  == NULL)
      err_sys("realloc failed");
  }
  strcpy(fullpath,pathname);
  strcpy(filename,pathname);
  return(dopath(func));
}

static int dopath(Myfunc *func){
  struct stat statbuf;
  struct dirent *dirp;
  DIR *dp;
  int ret,n;

  if(lstat(filename,&statbuf) < 0)
    return(func(fullpath,&statbuf,FTW_NS));
  if(S_ISDIR(statbuf.st_mode) == 0)
    return(func(fullpath,&statbuf,FTW_F));

  if((ret = func(fullpath,&statbuf,FTW_D)) != 0)
    return(ret);
  //printf("fullpath is %s\n",fullpath);
  if(chdir(fullpath) != 0)
    err_sys("chdir %s failed\n",fullpath);
  n = strlen(fullpath);
  if(n + NAME_MAX + 2 > pathlen){
    pathlen *= 2;
    if((fullpath = realloc(fullpath,pathlen)) == NULL)
      err_sys("realloc failed");
  }
  fullpath[n++] = '/';
  fullpath[n] = 0;
  if((dp = opendir(fullpath)) == NULL){
    return(func(fullpath,&statbuf,FTW_DNR));
  }
  while((dirp = readdir(dp)) != NULL){
    if(strcmp(dirp->d_name,".") == 0 ||
       strcmp(dirp->d_name,"..") == 0)
      continue;
    strcpy(&fullpath[n],dirp->d_name);
    strcpy(filename,dirp->d_name);
    if((ret = dopath(func)) != 0)
      break;
  }
  if(chdir("..") != 0)
    err_sys("chdir %s failed\n",fullpath);
  fullpath[n-1] = 0;
  if(closedir(dp) < 0)
    err_ret("can't close dir %s",fullpath);


  return(ret);
}
static int myfunc(const char *pathname,const struct stat *statptr,int type){
  switch(type){
  case FTW_F:
    switch(statptr->st_mode & S_IFMT){
    case S_IFREG: nreg++;break;
    case S_IFBLK: nblk++;break;
    case S_IFCHR: nchr++;break;
    case S_IFIFO: nfifo++;break;
    case S_IFLNK: nslink++;break;
    case S_IFSOCK: nsock++;break;
    case S_IFDIR: err_dump("for S_IFDIR for %s:",pathname);
    }
    break;
  case FTW_D:
    ndir++;
    break;
  case FTW_NS:
    err_ret("stat error for %s:",pathname);
    break;
  default:
    err_dump("unknown type %d for pathname %s",type,pathname);
  }
  return(0);
}
/*static char *path_alloc(int* size) {
  char *p = NULL;
  if(!size) return NULL;
  p = malloc(256);
  if(p)
    *size = 256;
  else
    *size = 0;
  return p;
}*/
