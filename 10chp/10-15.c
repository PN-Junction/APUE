#include "apue.h"
#include <time.h>  
#include <setjmp.h>  
#include <errno.h>  
  
static void sig_usr1(int),sig_alrm(int);  
static sigjmp_buf jmpbuf;  
static volatile sig_atomic_t canjmp;  
void pr_mask(const char* str);  
  
int main(void)  
{  
        if(signal(SIGUSR1,sig_usr1)==SIG_ERR)  
        {  
                err_sys("signal(SIGUSR1) error\n");  
        }  
        if(signal(SIGALRM,sig_alrm)==SIG_ERR)  
        {  
                err_sys("signal(AIGALRM) error\n");  
        }  
        pr_mask("starting main:");  
  
        if(sigsetjmp(jmpbuf,1))  
//        if(setjmp(jmpbuf))  
        {  
                pr_mask("ending main:");  
                exit(0);  
        }  
        canjmp = 1;  
  
        for(;;)  
                pause();  
  
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
                printf("%s\n",str);  
  
                if(sigismember(&sigset,SIGINT)) printf(" SIGINT");  
  
                if(sigismember(&sigset,SIGQUIT)) printf(" SIGQUIT");  
                if(sigismember(&sigset,SIGUSR1)) printf(" SIGUSR1");  
                if(sigismember(&sigset,SIGALRM)) printf(" SIGALRM");  
  
                printf("\nthat's all\n");  
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
  
static void sig_alrm(int signo)  
{  
        pr_mask("in sig_alrm:");  
}  
