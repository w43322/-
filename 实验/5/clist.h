#ifndef CLIST_H
#define CLIST_H

#include<list>//包含STL中的list
class CList//自定义的循环链表类
{
private:
    std::list<int>Data;//底层是线性链表
    std::list<int>::iterator it;//指针
public:
    void push_back(int x);//加入新元素
    int size();//返回元素个数
    void erase_prev();//删除指针所指向的元素，并让指针指向上一个元素
    void erase_next();//删除指针所指向的元素，并让指针指向下一个元素
    void prev();//让指针指向上一个元素
    void next();//让指针指向下一个元素
    int get();//获取指针当前指向的元素
};

#endif //CLIST_H