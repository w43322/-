#include<iostream>
#include<queue>
#include<map>
using namespace std;

class treeNode
{
public:
    int data,freq;
    treeNode *lchild,*rchild;
    treeNode(int DATA,int FREQ)
    {
        this->data=DATA;
        this->freq=FREQ;
        this->lchild=NULL;
        this->rchild=NULL;
    }
    bool operator<(treeNode other)const
    {
        return this->freq<other.freq;
    }
    bool operator>(treeNode other)const
    {
        return this->freq>other.freq;
    }
};
treeNode *join(treeNode *A,treeNode *B)
{
    treeNode *res=new treeNode(0,A->freq+B->freq);
    res->lchild=A;
    res->rchild=B;
    return res;
}
void DFS(map<int,string>&HuffmanCode,treeNode *nownode,string nowstr)
{
    //printf("node:%p data:%d freq:%d l:%p r:%p\n",nownode,nownode->data,nownode->freq,nownode->lchild,nownode->rchild);
    //cout<<"str:"<<nowstr<<endl;
    if(!(nownode->lchild||nownode->rchild))
    {
        HuffmanCode[nownode->data]=nowstr;
        return;
    }
    if(nownode->lchild)
        DFS(HuffmanCode,nownode->lchild,nowstr+"0");
    if(nownode->rchild)
        DFS(HuffmanCode,nownode->rchild,nowstr+"1");
}
struct cmp
{
    bool operator ()(treeNode *A,treeNode *B)
    {
        return A->freq>B->freq;
    }
};
int main()
{
    string str="Something in the way she moves\
Attracts me like no other lover\
Something in the way she woos me\
I don't want to leave her now\
You know I believe and how\
Somewhere in her smile she knows\
That I don't need no other lover\
Something in her style that shows me\
I don't want to leave her now\
You know I believe and how\
You're asking me will my love grow\
I don't know, I don't know\
You stick around, now it may show\
I don't know, I don't know\
Something in the way she knows\
And all I have to do is think of her\
Something in the things she shows me\
I don't want to leave her now\
You know I believe and how";
    map<int,int>mp;
    priority_queue<treeNode*,vector<treeNode*>,cmp>pq;
    
    //count each char
    for(int i=0;i<str.length();++i)
        mp[str[i]]++;
    
    //generate huffman tree
    for(auto i:mp)
    {
        treeNode *newnode=new treeNode(i.first,i.second);
        //cout<<newnode->data<<" "<<newnode->freq<<endl;
        pq.push(newnode);
    }
    while(pq.size()>1)
    {
        treeNode *fir=pq.top();
        pq.pop();
        treeNode *sec=pq.top();
        pq.pop();
        treeNode *newnode=join(fir,sec);
        pq.push(newnode);
    }

    //get huffman coding
    map<int,string>HuffmanCode;
    DFS(HuffmanCode,pq.top(),"");

    for(auto i:HuffmanCode)
    {
        cout<<(char)i.first<<" "<<i.second<<endl;
    }

    //get compressed string
    string ans;
    for(int i=0;i<str.length();++i)
        ans+=HuffmanCode[str[i]];
    cout<<ans<<endl;

    //comparison
    cout<<ans.length()<<"/"<<str.length()*8<<endl;
}