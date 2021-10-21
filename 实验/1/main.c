#include"main.h"
int main()
{
    char tmp[max_element_count];
    SqList set_a,set_b;
    printf("\n----------输入----------\n");
    printf("\n请输入集合A中的元素（每个元素为一个数字或小写字母，元素之间不加空格）：");
    scanf("%s",tmp);
    init(&set_a,tmp);
    printf("\n请输入集合B中的元素（每个元素为一个数字或小写字母，元素之间不加空格）：");
    scanf("%s",tmp);
    init(&set_b,tmp);

    //print(&set_a);
    //print(&set_b);

    printf("\n----------输出----------\n");
    printf("\n集合A：");
    print(&set_a);
    printf("\n集合B：");
    print(&set_b);
    SqList set_t;
    get_union(&set_a,&set_b,&set_t);
    printf("\n集合A并B：");
    print(&set_t);
    get_intersection(&set_a,&set_b,&set_t);
    printf("\n集合A交B：");
    print(&set_t);
    get_diff(&set_a,&set_b,&set_t);
    printf("\n集合A-B：");
    print(&set_t);
    printf("\n-----------完成----------\n");

    return 0;
}
/*
cd "/Users/w43322/Desktop/code/data_structure_assignment/实验/1/" && gcc main.c sqlist.c -o main && "/Users/w43322/Desktop/code/data_structure_assignment/实验/1/"main
*/

/*
3、集合的并交差运算
【问题描述】
设计一个能演示集合的并、交、差运算程序。
【实验要求】
（1）采用顺序表或链表等数据结构。
（2）集合的元素限定为数字和小写英文字母。
*/