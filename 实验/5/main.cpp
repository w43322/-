#include"main.h"
int main()
{
    int N,M;
    CList L;

    std::cout<<"约瑟夫环问题:\n"
             <<"N个人围成一圈，从第一个人开始报数，数到M的人出列，再由下一个人重新从1开始报数，\n"
             <<"数到M的人再出圈，依次类推，直到所有的人都出圈，\n";
    std::cout<<"    请输入N和M(1<=M<=N):";
    std::cin>>N>>M;
    while(1>M||M>N)
    {
        std::cout<<"输入错误，请重新输入!\n";
        std::cout<<"    请输入N和M(1<=M<=N):";
        std::cin>>N>>M;
    }
    std::cout<<"----------START-OF-OUTPUT----------------\n"
             <<"出圈的人的编号依次为:\n    ";

    for(int i=1;i<=N;++i)
        L.push_back(i);
    
    int cnt=M;
    while(L.size())
    {
        while(cnt--)
            L.next();
        std::cout<<L.get()<<" ";
        L.erase();
        cnt=M;
    }
    std::cout<<"\n----------END-OF-OUTPUT------------------\n";
}

/*
4、STL的双向循环链表类
（1）实现STL的双向循环链表类。
（2）双向循环链表类的简单应用。
*/