#include<iostream>
#include<ctime>
int main()
{
    

    int T=1;
    while(T--)
    {
        FILE *fil=fopen("in.txt","w");
        srand(clock());
        int N=500;
        int M=500;
        int E=rand()%(N*M);
        fprintf(fil,"%d %d %d\n",N,M,E);
        for(int i=1;i<=E;++i)
        {
            int u=rand()%N+1;
            int v=rand()%M+1;
            fprintf(fil,"%d %d\n",u,v);
        }

        fclose(fil);

        system("./dinic");

        system("./hungary");
    }
}