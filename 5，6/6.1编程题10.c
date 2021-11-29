//二叉树结点的平衡因子（bf）定义为该结点的左子树高度与右子树高度之差。
//设二叉树结点结构为：(lchild,data,bf,rchild),
//lchild,rchild 是左右儿子指针；data是数据元素；bf是平衡因子，
//编写递归算法计算二叉树中各个结点的平衡因子
#include<stdio.h>
typedef struct TREENODE
{
    int data,bf;
    struct TREENODE *lchild,*rchild;
}TreeNode;
int max(const int a,const int b)
{
    return a>b?a:b;
}
int TreeHeight(TreeNode* T)//返回树的高度
{
    if(T==NULL)
        return 0;
    else
        return max(TreeHeight(T->lchild)+1,TreeHeight(T->rchild)+1);
}
void InitTreeBf(TreeNode* T)//初始化bf
{
    if(T==NULL)
        return;
    else
    {
        InitTreeBf(T->lchild);
        InitTreeBf(T->rchild);
        T->bf=TreeHeight(T->lchild)-TreeHeight(T->rchild);
    }
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
    set(&B,&D,0);
    set(&C,0,0);
    set(&D,&E,0);
    set(&E,0,&F);
    set(&F,0,0);
    InitTreeBf(&A);
    printf("%d\n",A.bf);
    //输出3
    printf("%d\n",B.bf);
    //输出3
    printf("%d\n",C.bf);
    //输出0
}
