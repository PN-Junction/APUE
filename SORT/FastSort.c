#include <stdio.h>
#include <stdlib.h>
#define NUM 5

int FastPos(int * arr,int low,int high){
    int val = arr[low];
    while(low < high){
       while(low < high && arr[high] >= val) 
         high--;
       arr[low] = arr[high];
       while(low < high && arr[low] <= val) 
         low++;
       arr[high] = arr[low];
    }
    arr[low] = val;
    printf("%d pos on %d\n",val,low);
    return low;
}

void FastSort(int * arr,int low,int high){
    int pos;
    if(low < high){
        pos = FastPos(arr,low,high);
        FastSort(arr,low,pos-1);
        FastSort(arr,pos+1,high);
    }
}

int main(int argc,char **argv){
    int i = 0,j=0,a;
    int *val;
    int arr[NUM]={-1,-2,0,0,4};
    int tmp;
    //for(i=0;i<NUM;i++)
    //  arr[i] = random()%100;
    for(i=0;i<NUM;i++)
      printf("%d ",arr[i]);
    printf("\n");

    FastSort(arr,0,NUM-1);

    for(i=0;i<NUM;i++)
      printf("%d ",arr[i]);
    printf("\n");
}
