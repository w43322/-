typedef int ElemType;
typedef node* iterator;

class node
{
    ElemType data;
    node *next,*prev;
};
class mylist
{
    int SIZE;
    iterator head;
    iterator tail;
    
    mylist();
    ~mylist();
    iterator begin();
    iterator end();
    ElemType front();
    ElemType back();
    void push_front(ElemType);
    void pop_front();
    void push_back(ElemType);
    void pop_back();
};