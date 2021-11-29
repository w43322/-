//一棵二叉树以二叉链表来表示，编写算法 ，求其指定的某一层k(k>1)上的叶子结点的个数。
#include<stdio.h>
typedef struct TREENODE
{
    int val;
    struct TREENODE *lchild,*rchild;
}TreeNode;
int CountLeaf(TreeNode* T,int x,int k)//T为当前节点;x为当前层;k为目标层
{
    int res=0;
    if(x>k)
        return 0;
    if(x==k&&T->lchild==NULL&&T->rchild==NULL)
        return 1;
    if(T->lchild)
        res+=CountLeaf(T->lchild,x+1,k);
    if(T->rchild)
        res+=CountLeaf(T->rchild,x+1,k);
    return res;
}
void set(TreeNode* X,TreeNode *L,TreeNode *R)
{
    X->lchild=L;
    X->rchild=R;
}
int main()
{
    TreeNode A,B,C,D,E;
    set(&A,&B,&C);
    set(&B,&D,&E);
    set(&C,0,0);
    set(&D,0,0);
    set(&E,0,0);
    printf("%d\n",CountLeaf(&A,1,3));
    //调用时第一个参数填树根，第二个参数填1，第三个参数填k
}
