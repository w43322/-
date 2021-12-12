#include"clist.h"
CList::CList()
{
    it=Data.end();
}
void CList::push_back(int x)
{
    Data.push_back(x);
    it=Data.end();
}
int CList::size()
{
    return Data.size();
}
void CList::erase()
{
    Data.erase(it);
}
void CList::next()
{
    ++it;
    if(it==Data.end())
        it=Data.begin();
}
int CList::get()
{
    return *it;
}