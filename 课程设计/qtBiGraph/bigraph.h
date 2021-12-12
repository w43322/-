#ifndef BIGRAPH_H
#define BIGRAPH_H

#include<queue>
#include<vector>
#include<unordered_map>
#include<map>

//mac
#define unordered_multimap multimap
#define unordered_map map

class BiGraph
{
private:
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
    int n1,m1;
    std::unordered_multimap<int,int>L;//starting point,edge index
    std::vector<Edge>edge;
    std::vector<int>level;

    void _add(int u,int v,int value);
    bool bfs();
    int dfs(int x,int y);
    void _addedge(int u,int v,int value);

public:
    void AddEdge(int u,int v,int value);
    BiGraph(int n,int m);
    int dinic();
    std::unordered_multimap<int,int>GetEdges(int);
};


#endif // BIGRAPH_H

