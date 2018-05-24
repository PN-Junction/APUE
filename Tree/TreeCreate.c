#include<stdio.h>
#include<stdlib.h>

static int parr=0;
static char arr[]="AB#D##C##";

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;


int PreCreateBiTree(BiTree * T){
    char ch;
    ch = arr[parr];
    parr ++;
//    scanf("%c",&ch);
    if(ch == '#')
        *T == NULL;
    else{
        *T = (BiTree)malloc(sizeof(BiTree));
        if(!*T)
            return -1;
        (*T)->data = ch;
        PreCreateBiTree(&(*T)->lchild);
        PreCreateBiTree(&(*T)->rchild);
    }
    return 0;
}
/*
int PostCreateBiTree(BiTree * T){
    char ch;

    PostCreateBiTree(&(*T)->lchild);
    PostCreateBiTree(&(*T)->rchild);
    scanf("%c",&ch);
    if(ch == '#')
        (*T) == NULL;
    else{
        *T = (BiTree)malloc(sizeof(BiTree));
        if(!*T)
            return -1;
        (*T)->data = ch;
    }
    return 0;
}
*/
void InOrderTraverse(BiTree T){
    if(T == NULL)
        return;
    InOrderTraverse(T->lchild);
    printf("%c",T->data);
    InOrderTraverse(T->rchild);
}

void PostOrderTraverse(BiTree T){
    if(T == NULL)
        return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c",T->data);
}

void PreOrderTraverse(BiTree T){
    if(T == NULL)
        return;
    printf("%c",T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

int main(int argc,char **argv){
   
    int res;
    BiTree T; 

    res = PreCreateBiTree(&T);
    if(res == -1)
        exit(-1);
    PreOrderTraverse(T);
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
    printf("\n");

}
