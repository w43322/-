#include"mylist.h"
mylist::mylist()
{
    this->head=nullptr;
    this->tail=nullptr;
    this->SIZE=0;
}
mylist::~mylist()
{

}
iterator mylist::begin()
{
    return this->head;
}
iterator mylist::end()
{
    return this->tail;
}
ElemType mylist::front()
{
    return *this->head;
}
ElemType mylist::back()
{
    return *this->tail;
}
void mylist::push_front(ElemType elem)
{
    iterator newnode=new node;
    newnode->data=elem;
    newnode->prev=nullptr;
    newnode->next=this->head;

    if(this->head)
        this->head->prev=newnode;
    if(this->tail==nullptr)
        this->tail=newnode;
    this->head=newnode;
    ++this->SIZE;
}
void mylist::pop_front()
{

}