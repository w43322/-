#include<vector>
#include<iostream>
#include<queue>
#include<cstring>
#include<ctime>

using namespace std;

#define maxn 10000+10

struct Edge
{
    int from, to, R;
    Edge(int u, int v, int r) : from(u), to(v), R(r) {}
};

int  s, t;
vector<Edge> edges;
vector<int> G[maxn];
int d[maxn], cur[maxn];
bool vis[maxn];

  void AddEdge(int from, int to) {
    edges.push_back(Edge(from, to, 1));
    edges.push_back(Edge(to, from, 0));
    int m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }

  bool BFS()
  {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    d[s] = 0;
    vis[s] = 1;
    while(!Q.empty())
    {
      int u = Q.front();
      Q.pop();
      int siz=G[u].size();
      for (int i = 0; i < siz; i++)
      {
        Edge& e = edges[G[u][i]];
        if (!vis[e.to] && e.R)
        {
          vis[e.to] = 1;
          d[e.to] = d[u] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  int DFS(int u)
  {
    if(u==t)return 1;
    int siz=G[u].size();
    for(int &i=cur[u];i<siz;++i)
    {
      Edge &e=edges[G[u][i]];
      if(e.R&&d[u]+1==d[e.to]&&DFS(e.to))
      {
        e.R=0;
        edges[G[u][i]^1].R=1;
        return 1;
      }
    }
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
    freopen("in.txt","r",stdin);
    freopen("out_d.txt","w",stdout);
    clock_t START=clock();
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
    clock_t END=clock();
    printf("%.2f\n",(double)(END-START)/CLOCKS_PER_SEC);
}