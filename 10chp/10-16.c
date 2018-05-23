#include "apue.h"
#include <time.h>  
#include <setjmp.h>  
#include <errno.h>  
  
static void sig_usr1(int),sig_int(int);  
static sigjmp_buf jmpbuf;  
static volatile sig_atomic_t canjmp;  
void pr_mask(const char* str);  
  
int main(void)  
{  
 sigset_t newmask,oldmask,watimask; 
 pr_mask("program start: ");

 if(signal(SIGINT,sig_int) == SIG_ERR)
   err_sys("signal(SIGINT) err");

 sigemptyset(&watimask);
 sigaddset(&watimask,SIGUSR1);
 sigemptyset(&newmask);
 sigaddset(&newmask,SIGINT);


 if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
   err_sys("SIG_BLOCK err");


 pr_mask("in critical region:");

 if(sigsuspend(&watimask) != -1)
   err_sys("sigsuspend err");

 pr_mask("return from sigsuspend: ");

 if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
   err_sys("SIG_SETMASK err");

 pr_mask("program exit: ");
 exit(0);
}  
  
void pr_mask(const char* str)  
{  
        sigset_t sigset;  
        int errno_save;  
  
        errno_save = errno;  
        if(sigprocmask(0,NULL,&sigset)<0)  
        {  
                err_ret("sigprocmask error\n");  
        }
        else{
                printf("%s",str);  
  
                if(sigismember(&sigset,SIGINT)) printf(" SIGINT");  
  
                if(sigismember(&sigset,SIGQUIT)) printf(" SIGQUIT");  
                if(sigismember(&sigset,SIGUSR1)) printf(" SIGUSR1");  
                if(sigismember(&sigset,SIGALRM)) printf(" SIGALRM");  
  
                printf("\n########################\n");  
        }
  
        errno = errno_save;  
}  
  
static void sig_usr1(int signo)  
{  
        time_t starttime;  
        if(canjmp == 0)  
                return;  
  
        pr_mask("in sig_usr1:");  
  
        alarm(3);  
        starttime = time(NULL);  
  
        for(;;)  
        {  
                if(time(NULL)>starttime+5)  
                {  
                        break;  
                }  
        }  
  
        pr_mask("ending sig_usr1:");  
        canjmp = 0;
  
        //longjmp(jmpbuf,1);  
        siglongjmp(jmpbuf,1);  
}  
  
static void sig_int(int signo)  
{  
        pr_mask("\nin sig_int:");  
}  
