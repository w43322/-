//已知中序线索二叉树T右子树不空。设计算法，
//将S所指的结点作为T的右子树中的一个叶子结点插入进去，
//并使之成为T的右子树的（中序序列）第一个结点（同时要修改相应的线索关系）
#include<stdio.h>
typedef struct TREENODE
{
    int data,Ltag,Rtag;
    struct TREENODE *lchild,*rchild;
}TreeNode;
void add(TreeNode *T,TreeNode *S)//T,S同题中定义
{
    TreeNode *R=T->rchild;
    while(R->Ltag==0)
        R=R->lchild;
    //查找第一个中序序列第一个叶子节点
    S->Ltag=1;
    S->lchild=R->lchild;
    S->Rtag=1;
    S->rchild=R;
    //更新新插入的节点的信息
    R->Ltag=0;
    R->lchild=S;
    //更新原来节点的信息
}
int main()
{
    return 0;
}
