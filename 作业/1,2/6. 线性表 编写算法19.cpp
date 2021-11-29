//已知线性表中的元素以值递增有序排列，并以单链表作存储结构。试编写一高效算法，删除表中所有值大于mink且小于maxk的元素（若表中存在这样的元素），同时释放被删除结点空间，并分析算法的时间复杂度。

#include"linklist.h"

Status ListSectionDelete_L(LinkList &L,ElemType mink,ElemType maxk)
{
    LinkList p=L,a=L,prev;
    while(p->data<=mink)
    {
        a=p;
        p=p->next;
    }
    while(p->data<maxk)
    {
        prev=p;
        p=p->next;
        free(prev);
    }
    a->next=p;
    return OK;
}

//时间复杂度：因为链表是有序的，只从头开始遍历了一次链表，而链表对于元素的删除的时间复杂度是O(1)，因此算法时间复杂度是O(maxk的位置)，具体的时间复杂度要取决于maxk的位置，最坏情况下是O(表长)。