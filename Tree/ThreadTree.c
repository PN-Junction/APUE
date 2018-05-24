#include<stdio.h>
#include<stdlib.h>

#define LINK    0
#define THREAD  1

static int parr=0;
static char arr[]="AB#D##C##";

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
    int LTag;
    int RTag;
}BiTNode,*BiTree;

BiTree pre=NULL;
void InThreading(BiTree p){

    if(p != NULL){
        InThreading(p->lchild);

        if(p->lchild == NULL){
            p->LTag = THREAD;
            p->lchild = pre;
        }
        if(pre != NULL && pre->rchild == NULL ){
            pre->RTag = THREAD;
            pre->rchild = p;
        }
        pre = p;

        InThreading(p->rchild);
    }

}

void PreThreading(BiTree p){

    if(p != NULL){

        if(p->lchild == NULL){
            p->LTag = THREAD;
            p->lchild = pre;
        }
        if(pre != NULL && pre->rchild == NULL ){
            pre->RTag = THREAD;
            pre->rchild = p;
        }
        pre = p;

        //由于 顺序为： 根-左-右
        //根会将左右孩子节点先定义为前驱 后继节点
        //如果此时直接进行前驱和后继的线索化 会发生死递归 
        if(p->LTag == LINK)                 
            InThreading(p->lchild);
        if(p->RTag == LINK)
            InThreading(p->rchild);

    }

}
// 前两中方法不适用于后序线索化 后序线索化顺序为： 左-右-根
// 在左 右 都确定好前驱 后继以后 如果根节点的度为2 
// 则 无法找到根点后继 无法形成线性链表

int InOrderTraverse_Thr(BiTree T){
    BiTree p = T;
    while(p != NULL){
        while(p->LTag == LINK)
            p = p->lchild;
        printf("%c",p->data);
        while(p->RTag == THREAD && p->rchild != NULL){
            p = p->rchild;
            printf("%c",p->data);
        }
        p = p->rchild;
    }
    return 0;
}

int PreOrderTraverse_Thr(BiTree T){
    BiTree p = T;
    while(p != NULL){
        while(p!=NULL && p->LTag == LINK){
            printf("%c",p->data);
            p = p->lchild;
        }
        printf("%c",p->data);
        p = p->rchild;
    }
    return 0;
}


int PreCreateBiTree(BiTree * T){
    char ch;
    ch = arr[parr];
    parr ++;
//    scanf("%c",&ch);
    if(ch == '#')
        *T == NULL;
    else{
        *T = (BiTree)malloc(sizeof(BiTNode));
        if(!*T)
            return -1;
        (*T)->data = ch;
        (*T)->LTag = (*T)->RTag = LINK;
        PreCreateBiTree(&(*T)->lchild);
        PreCreateBiTree(&(*T)->rchild);
    }
    return 0;
}

int main(int argc,char **argv){
   
    int res;
    BiTree T,T_Thr; 

    res = PreCreateBiTree(&T);
    if(res == -1)
        exit(-1);
    PreThreading(T);
    PreOrderTraverse_Thr(T);
    printf("\n");


}
