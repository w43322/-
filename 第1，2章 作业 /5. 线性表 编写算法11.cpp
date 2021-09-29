//设顺序表va中的数据元素递增有序。试写一算法，将x插入到顺序表的适当位置上，以保持该表的有序性

#include"sqlist.h"

Status ListInsert_Sq(SqList &L,int i,ElemType e)
{
    if(i<1||i>L.length+1)return ERROR;
    if(L.length>=L.listsize)
    {
        ElemType* newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)exit(OVERFLOW);
        L.elem=newbase;
        L.listsize+=LISTINCREMENT;
    }
    ElemType* q=&(L.elem[i-1]);
    for(ElemType* p=&(L.elem[L.length-1]);p>=q;--p)
        *(p+1)=*p;
    *q=e;
    ++L.length;
    return OK;
}

Status AccendListInsert_Sq(SqList &va,ElemType x)
{
    int p=0;
    while(x>*(va.elem+p))++p;
    return ListInsert_Sq(va,p+1,x);
}