#include"tree.h"
int FindLastDot(const char *URL)
{
    for(int i=strlen(URL);i>=0;--i)
        if(URL[i]=='.')return i;
    return -1;
}
TreeNode *AddChild(TreeNode *root,const char *data)
{
    printf("             data:    %s\n",data);
    TreeNode* NewNode=Find(root,data);
    if(NewNode==NULL)
    {
        NewNode=(TreeNode*)malloc(sizeof(TreeNode));
        strcpy(NewNode->data,data);
        NewNode->firstchild=NULL;
        NewNode->nextsibling=NULL;
        NewNode->terminate=0;
        if(root->firstchild)
        {
            TreeNode *NowNode=root->firstchild;
            while(NowNode->nextsibling)
                NowNode=NowNode->nextsibling;
            NowNode->nextsibling=NewNode;
        }
        else
        {
            root->firstchild=NewNode;
        }
    }
    return NewNode;
}
void Add(TreeNode *root,const char *URL)
{
    printf("Adding:\n    remaining_url:    %s\n",URL);
    int pos=FindLastDot(URL);
    char NextURL[max_string_length];
    if(pos!=-1)
    {
        TreeNode *child=AddChild(root,URL+pos+1);
        memcpy(NextURL,URL,pos*sizeof(char));
        NextURL[pos]='\0';
        Add(child,NextURL);
    }
    else
    {
        TreeNode *child=AddChild(root,URL+pos+1);
        child->terminate=1;
    }
}
TreeNode* Find(TreeNode *root,const char *URL)
{
    //printf("Finding: remaining_url:%s\n",URL);
    int pos=FindLastDot(URL);
    char NextURL[max_string_length];
    if(pos!=-1)
    {
        //printf("         part_to_comp:%s\n",URL+pos+1);
        TreeNode *NowNode=root->firstchild;
        while(NowNode)
        {
            if(strcmp(NowNode->data,URL+pos+1)==0)
            {
                memcpy(NextURL,URL,pos*sizeof(char));
                NextURL[pos]='\0';
                return Find(NowNode,NextURL);
            }
            NowNode=NowNode->nextsibling;
        }
        return NULL;
    }
    else
    {
        //printf("         part_to_comp:%s\n",URL);
        TreeNode *NowNode=root->firstchild;
        while(NowNode)
        {
            if(strcmp(NowNode->data,URL)==0)
            {
                //printf("found existing node\n");
                return NowNode;
            }
            NowNode=NowNode->nextsibling;
        }
        return NULL;
    }
}
void DFS(TreeNode *root,const char *URL)
{
    char NewURL[max_string_length];
    if(strlen(URL)==0)
        strcpy(NewURL,root->data);
    else
        sprintf(NewURL,"%s.%s",root->data,URL);
    if(root->terminate)
        printf("%s\n",NewURL);
    TreeNode *child=root->firstchild;
    while(child)
    {
        DFS(child,NewURL);
        child=child->nextsibling;
    }
}
void BFS(TreeNode *root)
{
    Queue *q=(Queue*)malloc(sizeof(Queue));
    Init(q);
    Push(q,root);
    int lvl=0;
    int now_lvl_cnt=1;
    int next_lvl_cnt=0;
    while(!Empty(q))
    {
        TreeNode *NowNode=Pop(q);
        printf("%s ",NowNode->data);--now_lvl_cnt;
        TreeNode *child=NowNode->firstchild;
        while(child)
        {
            ++next_lvl_cnt;
            Push(q,child);
            child=child->nextsibling;
        }
        if(now_lvl_cnt==0&&next_lvl_cnt)
        {
            printf("\n---level:%d---\n",++lvl);
            now_lvl_cnt=next_lvl_cnt;
            next_lvl_cnt=0;
        }
    }
    free(q);
}
