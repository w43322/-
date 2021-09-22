//已知线性表中的元素以值递增有序排列，并以单链表作存储结构。试编写一高效算法，删除表中所有值大于mink且小于maxk的元素（若表中存在这样的元素），同时释放被删除结点空间，并分析算法的时间复杂度。

#include"linklist.h"

Status ListSectionDelete_L(LinkList &L,ElemType mink,ElemType maxk)
{
    LinkList p=L;
    while(p->data<=mink)
    {
        p=p->next;
    }
    while(p->data<maxk)
    {
        LinkList prev=p;
        p=p->next;
        free(prev);
    }
    return OK;
}