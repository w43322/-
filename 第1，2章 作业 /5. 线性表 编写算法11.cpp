//设顺序表va中的数据元素递增有序。试写一算法，将x插入到顺序表的适当位置上，以保持该表的有序性

#include"sqlist.h"

Status AccendListInsert_Sq(SqList &va,ElemType x)
{
    int p=0;
    while(x>*(va.elem+p))++p;
    return ListInsert_Sq(va,p+1,x);
}

int main()
{
    return 0;
}