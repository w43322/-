//#include<vector>
#include<iostream>
//#include<queue>
#include<cstring>

using namespace std;

#define maxn 1024

struct Edge
{
    int to, next, R;
}edges[maxn*maxn];
int edgecnt=0;

int  s, t;

int d[maxn], cur[maxn];

int head[maxn];

int Q[maxn],front=1,tail=0;

bool vis[maxn];

  void AddEdge(int from, int to) {
    edges[edgecnt].next=head[from];
    edges[edgecnt].to=to;
    edges[edgecnt++].R=1;
    edges[edgecnt].next=head[to];
    edges[edgecnt].to=from;
    edges[edgecnt++].R=0;
    head[from]=edgecnt-2;
    head[to]=edgecnt-1;
  }

  bool BFS()
  {
    memset(vis, 0, sizeof(vis));
    front=1;tail=0;
    Q[++tail]=s;
    d[s] = 0;
    vis[s] = 1;
    while(front<=tail)
    {
      int u = Q[front];
      ++front;
      for (int i=head[u];i;i=edges[i].next)
      {
        if (!vis[edges[i].to] && edges[i].R)
        {
          vis[edges[i].to] = 1;
          d[edges[i].to] = d[u] + 1;
          Q[++tail]=edges[i].to;
        }
      }
    }
    return vis[t];
  }

  int DFS(int u)
  {
    if(u==t)return 1;
    for(int i=head[u];i;i=edges[i].next)
    {
      Edge &e=edges[i];
      if(edges[i].R&&d[u]+1==d[edges[i].to]&&DFS(edges[i].to))
      {
        edges[i].R=0;
        edges[i^1].R=1;
        return 1;
      }
    }
    /*for(int &i=cur[u];i<G[u].size();++i)
    {
      Edge &e=edges[G[u][i]];
      if(e.R&&d[u]+1==d[e.to]&&DFS(e.to))
      {
        e.R=0;
        edges[G[u][i]^1].R=1;
        return 1;
      }
    }*/
    return 0;
  }

  int Maxflow()
  {
    int flow = 0;
    while (BFS())
    {
      memset(cur, 0, sizeof(cur));
      DFS(s);
      ++flow;
    }
    return flow;
  }

int main()
{
    //index starting from 
    int N,M,E;
    scanf("%d%d%d",&N,&M,&E);
    s=0;
    t=N+M+1;
    for(int i=1;i<=N;++i)
        AddEdge(0,i);
    for(int i=1;i<=M;++i)
        AddEdge(N+i,N+M+1);
    for(int i=1;i<=E;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        AddEdge(u,N+v);
    }
    printf("%d\n",Maxflow());
}