//编写一个函数或过程判定两棵二叉树是否相似，
//所谓两棵二叉树s和t相似，即是要么它们都为空或都只有一个结点，
//要么它们的左右子树都相似
#include<stdio.h>
typedef struct TREENODE
{
    int val;
    struct TREENODE *lchild,*rchild;
}TreeNode;
int Alike(TreeNode* T1,TreeNode* T2)//T1为第一棵树;T2为第二棵树
{
    if(T1==NULL)
        return T2==NULL;
    else if(T2==NULL)
        return T1==NULL;
    //如果一棵树为空，判断另一棵树是否为空
    //若都为空返回相似，否则返回不相似
    else
        return Alike(T1->lchild,T2->lchild)&&Alike(T1->rchild,T2->rchild);
    //如果两棵树皆非空，继续递归判断两棵树的左右子树是否相似
}
void set(TreeNode* X,TreeNode *L,TreeNode *R)
{
    X->lchild=L;
    X->rchild=R;
}
int main()
{
    TreeNode A,B,C,D,E,F;
    set(&A,&B,&C);
    set(&B,0,0);
    set(&C,0,0);
    set(&D,&E,0);
    set(&E,0,0);
    //判断时填写树根
    printf("%d\n",Alike(&A,&D));
    //不相似，输出0
    set(&D,&E,&F);
    set(&F,0,0);
    printf("%d\n",Alike(&A,&D));
    //相似，输出1
}
