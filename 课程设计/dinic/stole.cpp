#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<list>
#include<vector>
#include<unordered_map>
#define S 0
#define T n1+m1+1
#define N(x) x
#define M(x) n1+x
using namespace std;


int n1,m1,e1;
//int cnt=0;
unordered_multimap<int,int>L;
class Edge
{
public:
    int v,value;
    Edge(int a,int b)
    {
        v=a;
        value=b;
    }
};
vector<Edge>edge;
void add(int u,int v,int value)
{
    //L[u]=edge.size();
    L.insert(make_pair(u,edge.size()));
    edge.push_back(Edge(v,value));
    return;
}
void AddEdge(int u,int v,int value)
{
    add(u,v,value);
    add(v,u,0);
}
int level[1000001];
//dicnic暴力参见上面提到的博客。
bool bfs()
{
    int x,next;
    //memset(level,-1,sizeof(level));
    queue<int>Q;
    Q.push(S);
    level[S]=0;
    while(!Q.empty())
    {
        x=Q.front();
        Q.pop();
        auto Range=L.equal_range(x);
        for(auto it=Range.first;it!=Range.second;++it)
        {
            int &i=it->second;
            int v=edge[i].v;
            int value=edge[i].value;
            if(value&&level[v]<0)
            {
                Q.push(v);
                level[v]=level[x]+1;
            }
        }
    }
    if(level[T]==-1) return false;
    return true;
}
int dfs(int x,int y)
{
    printf("x:%d y:%d\n",x,y);
    if(x==T) return y;
    int w,used=0;
    auto Range=L.equal_range(x);
    for(auto it=Range.first;it!=Range.second;++it)
    {
        int &i=it->second;
        int v=edge[i].v;
        int value=edge[i].value;
        printf("v:%d value:%d\n",v,value);
        if(value&&level[v]==level[x]+1)
        {
                w=y-used;
                w=dfs(v,min(w,value));
                edge[i].value-=w;
                edge[i+1].value+=w;
                used+=w;
                if(used==y) return y;
        }
    }
    if(!used) level[x]=-1;
    return used;
}
int dinic()
{
    int res=0;
    while(bfs())
        res+=dfs(S,0x7fffffff);
    return res;
}


int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n1,&m1,&e1);
    for(int i=1;i<=n1;i++)
        AddEdge(S,N(i),1);
    for(int i=1;i<=e1;i++)
    {
    	int u,v;
    	scanf("%d%d",&u,&v);
    	AddEdge(N(u),M(v),1);
    }
    for(int i=1;i<=m1;i++)
        AddEdge(M(i),T,1);
    /*for(auto it=L.equal_range(0).first;it!=L.equal_range(0).second;++it)
    {
        auto i=*it;
        printf("node:%d edge_index:%d\n",i.first,i.second);
        Edge &e=edge[i.second];
        printf("  to:%d\n",e.v);
    }*/
    
    printf("%d",dinic());
    return 0;
}