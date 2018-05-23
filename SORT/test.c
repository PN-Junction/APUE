#include <stdio.h>
#include <stdlib.h>
#define NUM 5

int main(int argc,char **argv){
    int i = 0,j=0,a;
    int *val;
    unsigned char arr[NUM]={};
    unsigned char tmp;
    for(i=0;i<NUM;i++)
      arr[i] = random()%100;
    for(i=0;i<NUM;i++)
      printf("%d ",arr[i]);
    printf("\n");
    for(i=0;i<NUM-1;i++){
        for(j=NUM-i-1;j>=i;j--){
            if(arr[j]>arr[j+1]) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                for(a=0;a<NUM;a++)
                  printf("%d ",arr[a]);
                printf("\n");
            }
        }

    }
    //for(i=0;i<NUM;i++)
    //  printf("%d ",arr[i]);
    //printf("\n");
}
