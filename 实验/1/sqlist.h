#include"universal_header.h"
typedef struct
{
    char Data[max_element_count];
    int count;
}SqList;
void init(SqList*,char*);
int exist(SqList*,char);
int add(SqList*,char);
void print(SqList*);
void get_union(SqList*,SqList*,SqList*);
void get_intersection(SqList*,SqList*,SqList*);
void get_diff(SqList*,SqList*,SqList*);