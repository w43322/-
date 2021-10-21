#include"sqlist.h"
void init(SqList* s,char* str)
{
    s->count=0;
    for(int i=0;i<strlen(str);++i)
    {
        if(!exist(s,str[i]))
            add(s,str[i]);
        else
            printf("\nERROR: duplicate element:%c\n",str[i]);
    }
}
int exist(SqList* s,char c)
{
    for(int i=1;i<=s->count;++i)
    {
        if(s->Data[i]==c)
            return 1;
    }
    return 0;
}
int add(SqList* s,char c)
{
    if(s->count+1>=max_element_count)
        return ERROR;
    ++s->count;
    s->Data[s->count]=c;
    return OK;
}
void print(SqList* s)
{
    printf("\n集合中共有%d个元素：\n    ",s->count);
    for(int i=1;i<=s->count;++i)
        printf("%c ",s->Data[i]);
    printf("\n");
}
void get_union(SqList* a,SqList* b,SqList* t)
{
    init(t,"");
    for(int i=1;i<=a->count;++i)
        add(t,a->Data[i]);
    for(int i=1;i<=b->count;++i)
    {
        if(!exist(t,b->Data[i]))
            add(t,b->Data[i]);
    }
}
void get_intersection(SqList* a,SqList* b,SqList* t)
{
    init(t,"");
    for(int i=1;i<=a->count;++i)
    {
        if(exist(b,a->Data[i]))
            add(t,a->Data[i]);
    }
}
void get_diff(SqList* a,SqList* b,SqList* t)
{
    init(t,"");
    for(int i=1;i<=a->count;++i)
    {
        if(!exist(b,a->Data[i]))
            add(t,a->Data[i]);
    }
}