#include <stdio.h>
#include <string.h>

int main(int argc ,char **argv){
    //char *str=NULL;
    //char szstr[10]={};
    char szstr[10];
//    strcpy(szstr,"0123456789");
    szstr[0]=1;
    szstr[1]=2;
    szstr[2]=3;
    szstr[3]=4;
    szstr[4]=5;
    szstr[5]=6;
    szstr[6]=7;
    szstr[7]=8;
    szstr[8]=9;
    szstr[9]=0;
    printf("szstr is %d.\n",szstr[0]);
}
