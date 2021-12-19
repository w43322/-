#include"clist.h"
//本文件中包含CList中方法的实现
void CList::push_back(int x)//加入新元素
{
    Data.push_back(x);//把元素加入底层的线性链表
    it=Data.begin();//让指针指向表头
}
int CList::size()//返回元素个数
{
    return Data.size();//返回线性链表的元素个数
}
void CList::erase_next()//删除指针所指向的元素，并后移指针
{
    it=Data.erase(it);//删除当前指针所指向的元素
    if(it==Data.end())//如果已经来到表尾
        it=Data.begin();//那就指向表头
}
void CList::erase_prev()//删除指针所指向的元素，并前移指针
{
    it=Data.erase(it);//删除当前指针所指向的元素
    if(it==Data.begin())//如果已经在表头
        it=Data.end();//那就指向表尾
    --it;
}
void CList::next()//让指针指向下一个元素
{
    //说明：STL的list中的.end()迭代器中无元素，
    //所以如果自增以后来到Data.end()，为了符合循环链表的性质，
    //我们应让它指向表头元素。
    ++it;//尝试自增迭代器
    if(it==Data.end())//如果已经来到表尾
        it=Data.begin();//那就指向表头
    //如果没到表尾，什么都不做。
}
void CList::prev()//让指针指向上一个元素
{
    //说明：STL的list中的.begin()迭代器包含链表的第一个元素，
    //我们先查看迭代器是否为Data.begin()。
    //如果是的话我们应让它指向表尾元素。
    if(it==Data.begin())//如果已经在表头
        it=Data.end();//那就指向表尾
    --it;
    //但是.end()迭代器中没有元素，因此我们需要把它-1来指向真正的尾元素。
    //如果没在表头，也需要自减。
}
int CList::get()//获取指针当前指向的元素
{
    return *it;//返回指针指向的元素
}