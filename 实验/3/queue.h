#ifndef QUEUE_H
#define QUEUE_H

#include"universal_header.h"
typedef struct
{
    void* data[max_elem_cnt];
    int front,end;
}Queue;
void Init(Queue*);
int Push(Queue*,void*);
void *Pop(Queue*);
int Empty(Queue*);

#endif // QUEUE_H