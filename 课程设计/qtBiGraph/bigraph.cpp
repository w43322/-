#include "bigraph.h"

#include<QDebug>

#define S 0
#define T n1+m1+1
#define N(x) x
#define M(x) n1+x
void BiGraph::_add(int u,int v,int value)
{
    L.insert(std::make_pair(u,edge.size()));
    edge.push_back(Edge(v,value));
    return;
}
bool BiGraph::bfs()
{
    fill(level.begin(),level.end(),-1);
    std::queue<int>Q;
    Q.push(S);
    level[S]=0;
    while(!Q.empty())
    {
        int &x=Q.front();
        Q.pop();
        auto Range=L.equal_range(x);
        for(auto it=Range.first;it!=Range.second;++it)
        {
            int &i=it->second;
            int &v=edge[i].v;
            int &value=edge[i].value;
            if(value&&level[v]<0)
            {
                Q.push(v);
                level[v]=level[x]+1;
            }
        }
    }
    return level[T]!=-1;
}
int BiGraph::dfs(int x,int y)
{
    if(x==T) return y;
    int w,used=0;
    auto Range=L.equal_range(x);
    for(auto it=Range.first;it!=Range.second;++it)
    {
        int &i=it->second;
        int &v=edge[i].v;
        int &value=edge[i].value;
        if(value&&level[v]==level[x]+1)
        {
            w=y-used;
            w=dfs(v,std::min(w,value));
            edge[i].value-=w;
            edge[i+1].value+=w;
            used+=w;
            if(used==y) return y;
        }
    }
    if(!used) level[x]=-1;
    return used;
}
void BiGraph::_addedge(int u,int v,int value)
{
    _add(u,v,value);
    _add(v,u,0);
}
void BiGraph::AddEdge(int u,int v,int value)
{
    _addedge(N(u),M(v),value);
}
BiGraph::BiGraph(int n,int m)
{
    n1=n;
    m1=m;
    level.resize(T+1);
    for(int i=1;i<=n1;i++)
        _addedge(S,N(i),1);
    for(int i=1;i<=m1;i++)
        _addedge(M(i),T,1);
}
int BiGraph::dinic()
{
    int res=0;
    while(bfs())
        res+=dfs(S,0x7fffffff);
    return res;
}
std::unordered_multimap<int,int> BiGraph::GetEdges(int mode)
{
    qDebug()<<"mode:"<<mode;
    std::unordered_multimap<int,int>res;
    for(auto i:L)
    {
        int u=i.first,v=edge[i.second].v;
        int index=i.second;
        if(u>v)continue;
        if(mode==0)
        {
            if(u!=S)continue;
            if(edge[index+1].value==1)
            {
                res.insert(std::make_pair(0,v-1));
            }
        }
        else if(mode==1)
        {
            if(u==S||v==T)continue;
            if(edge[index+1].value==1)
            {
                res.insert(std::make_pair(u-1,v-n1-1));
            }
        }
        else if(mode==2)
        {
            if(v!=T)continue;
            if(edge[index+1].value==1)
            {
                res.insert(std::make_pair(u-n1-1,0));
            }
        }
    }
    return res;
}
#undef S
#undef T
#undef N
#undef M
