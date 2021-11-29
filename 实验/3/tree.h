#include"universal_header.h"
typedef struct TREENODE
{
    char data[max_string_length];
    struct TREENODE *firstchild,*nextsibling;
    int terminate;
}TreeNode;
int FindLastDot(const char *);
TreeNode *AddChild(TreeNode *,const char *);
void Add(TreeNode *,const char *);
TreeNode* Find(TreeNode *,const char *);