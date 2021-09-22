//试编写一算法，对单链表实现就地逆置，即利用原链表结点的存储空间，将线性表（a1,a2,...an）逆置为(an,an-1,...a1)。

#include"linklist.h"

Status ListReverse_L(LinkList &L)
{
    LinkList prev=L,now=L->next;
    L->next=NULL;
    while(now)
    {
        LinkList next=now->next;
        now->next=prev;
        prev=now;
        now=next;
    }
    return OK;
}