#define ElemType int
#define Status int

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 100

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#include<cstdio>
#include<cstdlib>

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

Status InitList_Sq(SqList &L)
{
    L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)exit(OVERFLOW);
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList&L,int i,ElemType e)
{
    
}