#include"queue.h"

void Init(Queue* Q)
{
    Q->front=1;
    Q->end=0;
    //printf("initializing queue...\n");
}
int Push(Queue* Q,void *root)
{
    if(Q->end+1>=max_elem_cnt)
        return printf("\nERROR: cannot push because queue is full!\n"),ERROR;
    ++Q->end;
    Q->data[Q->end]=root;
    return /*printf("%s:push success.\n",Q->Data[Q->end]),*/OK;
}
void *Pop(Queue* Q)
{
    if(Empty(Q))return printf("ERROR: cannot pop because queue is empty!\n"),NULL;
    ++Q->front;
    return Q->data[Q->front-1];
}
int Empty(Queue* Q)
{
    if(Q->front>Q->end)return /*printf("queue is empty.\n"),*/1;
    return /*printf("queue is not empty.\n"),*/0;
}