#ifndef CLIST_H
#define CLIST_H

#include<list>
class CList
{
private:
    std::list<int>Data;
    std::list<int>::iterator it;
public:
    CList();
    void push_back(int x);
    int size();
    void erase();
    void next();
    int get();
};

#endif //CLIST_H