#ifndef QUEUE_H
#define QUEUE_H

#include"universal_header.h"
typedef struct
{
    char Data[max_element_count][max_str_length];
    int front,end;
}Queue;
void init(Queue*);
int push(Queue*,char*);
int pop(Queue*,char*);
int empty(Queue*);

#endif //QUEUE_H