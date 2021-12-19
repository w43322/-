#include"queue.h"
void init(Queue* Q)
{
    Q->front=1;
    Q->end=0;
    //printf("initializing queue...\n");
}
int push(Queue* Q,char* str)
{
    if(Q->end+1>=max_element_count)
        return printf("\nERROR: cannot push because queue is full!\n"),ERROR;
    ++Q->end;
    for(int i=0;i<=strlen(str);++i)
        Q->Data[Q->end][i]=str[i];
    return /*printf("%s:push success.\n",Q->Data[Q->end]),*/OK;
}
int pop(Queue* Q,char* str)
{
    if(empty(Q))return printf("ERROR: cannot pop because queue is empty!\n"),ERROR;
    for(int i=0;i<=strlen(Q->Data[Q->front]);++i)
        str[i]=Q->Data[Q->front][i];
    ++Q->front;
    return /*printf("%s,pop success.\n",str),*/OK;
}
int empty(Queue* Q)
{
    if(Q->front>Q->end)return /*printf("queue is empty.\n"),*/1;
    return /*printf("queue is not empty.\n"),*/0;
}
int size(Queue* Q)
{
    return Q->end-Q->front+1;
}