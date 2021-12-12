#include<iostream>
#include<cstdio>

using namespace std;
const int maxn = 1e5 + 5;
int n1,n2,u,v,m,mat[maxn],st[maxn];//mat数组表示第i个节点是否被匹配，如果是0则是没被匹配
int h[maxn],e[maxn],nex[maxn],cnt = 1;

void add(int a, int b){
    e[cnt] = b;
    nex[cnt] = h[a];
    h[a] = cnt++;
}

int findE(int x){
    for(int i = h[x]; i != 0; i = nex[i]){
        int endd = e[i];
        if(!st[endd]){
            st[endd] = 1;
            if(mat[endd] == 0 || findE(mat[endd])){//没被匹配，或者匹配的人还有别的选择，则当前节点可以匹配此节点
                mat[endd] = x;
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    scanf("%d%d%d",&n1,&n2,&m);
    int a,b,ans = 0;
    while(m--){
        scanf("%d%d",&a,&b);
        add(a,b);
    }
    for(int i = 1; i <= n1; i++){
        memset(st,0,sizeof st);
        if(findE(i))ans++;//匹配到了匹配数目就加一
    }
    printf("%d",ans);
}