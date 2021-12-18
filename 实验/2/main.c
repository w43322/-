#include"main.h"
int main()
{
    int m,n,k;
    Queue M,N;
    init(&M);
    init(&N);
    printf("\n-----------请输入运动员信息----------\n");
    printf("\n请输入男运动员人数:");
    scanf("%d",&n);
    printf("\n请输入女运动员人数:");
    scanf("%d",&m);
    printf("\n请输入配对总轮数:");
    scanf("%d",&k);
    for(int i=1;i<=n;++i)
    {
        printf("\n请输入第%d个男运动员的名字（不含空格）:",i);
        char name[max_str_length];
        scanf("%s",name);
        push(&M,name);
    }
    for(int i=1;i<=m;++i)
    {
        printf("\n请输入第%d个女运动员的名字（不含空格）:",i);
        char name[max_str_length];
        scanf("%s",name);
        push(&N,name);
    }
    printf("\n-----------开始配对----------\n");
    int max_cnt=max(size(&M),size(&N));//男运动员多还是女运动员多？这个变量存最多的数量。
    int tot=0;//每个运动员都要至少比赛K次。
    for(int i=1;i<=k;++i)
    {
        printf("\n第%d轮配对:\n",i);
        for(int j=1;tot<max_cnt*i;++j)//进入循环的条件：这一轮配对中，还有人没比赛i次。
        {
            char name_m1[max_str_length],name_n1[max_str_length];
            pop(&M,name_m1);push(&M,name_m1);
            pop(&N,name_n1);push(&N,name_n1);
            char name_m2[max_str_length],name_n2[max_str_length];
            pop(&M,name_m2);push(&M,name_m2);
            pop(&N,name_n2);push(&N,name_n2);
            
            printf("  第%d场比赛:\n",j);
            printf("    Team 1:男运动员:%9s|女运动员:%9s\n",name_m1,name_n1);
            printf("    Team 2:男运动员:%9s|女运动员:%9s\n",name_m2,name_n2);
            tot+=2;
        }
    }
    printf("\n-----------完成----------\n");
    return 0;
}

/*
3、运动员混合双打组合 
【问题描述】
设有M个男羽毛球运动员和N个女羽毛球运动员，现进行男女混合双打组合K轮配对。男女运动员分别编号排队在等候队列，按顺序依次从男女运动员中各出队1人组合配对。本轮没成功配对者等待下一轮次配对。
【实验要求】
设计程序模拟完成运动员组合配对过程。
（1）采用队列等数据结构。
（2）输出每轮的配对信息。
*/