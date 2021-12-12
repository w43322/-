#ifndef GENERATOR_H
#define GENERATOR_H

#include"qbigraph.h"

QStringList RandomGenerate(QStringList Source,int &cnt)
{
    QStringList Dest;
    cnt=std::min(cnt,Source.size());
    std::random_shuffle(Source.begin(),Source.end());
    for(int i=0;i<cnt;++i)
    {
        Dest.push_back(Source[i]);
    }
    return Dest;
}
std::unordered_multimap<QString,QString> RandomGenerateLink(QStringList &strL1,QStringList &strL2)
{
    std::unordered_multimap<QString,QString> res;
    int EdgeCnt=strL1.size()+strL2.size();
    for(int i=0;i<EdgeCnt;++i)
    {
        int u=rand()%strL1.size(),v=rand()%strL2.size();
        qDebug("u:%d v:%d",u,v);
        res.insert(std::make_pair(strL1[u],strL2[v]));
    }
    return res;
}

QStringList TeachersSource=
{
    "James","Mary",
    "Robert","Patricia",
    "John","Jennifer",
    "Michael","Linda",
    "William","Elizabeth",
    "David","Barbara",
    "Richard","Susan",
    "Joseph","Jessica",
    "Thomas","Sarah",
    "Charles","Karen",
    "Christopher","Nancy",
    "Daniel","Lisa",
    "Matthew","Betty",
    "Anthony","Margaret",
    "Mark","Sandra",
    "Donald","Ashley",
    "Steven","Kimberly",
    "Paul","Emily",
    "Andrew","Donna",
    "Joshua","Michelle",
    "Kenneth","Dorothy",
    "Kevin","Carol",
    "Brian","Amanda",
    "George","Melissa",
    "Edward","Deborah",
    "Ronald","Stephanie",
    "Timothy","Rebecca",
    "Jason","Sharon",
    "Jeffrey","Laura",
    "Ryan","Cynthia",
    "Jacob","Kathleen",
    "Gary","Amy",
    "Nicholas","Shirley",
    "Eric","Angela",
    "Jonathan","Helen",
    "Stephen","Anna",
    "Larry","Brenda",
    "Justin","Pamela",
    "Scott","Nicole",
    "Brandon","Emma",
    "Benjamin","Samantha",
    "Samuel","Katherine",
    "Gregory","Christine",
    "Frank","Debra",
    "Alexander","Rachel",
    "Raymond","Catherine",
    "Patrick","Carolyn",
    "Jack","Janet",
    "Dennis","Ruth",
    "Jerry","Maria",
    "Tyler","Heather",
    "Aaron","Diane",
    "Jose","Virginia",
    "Adam","Julie",
    "Henry","Joyce",
    "Nathan","Victoria",
    "Douglas","Olivia",
    "Zachary","Kelly",
    "Peter","Christina",
    "Kyle","Lauren",
    "Walter","Joan",
    "Ethan","Evelyn",
    "Jeremy","Judith",
    "Harold","Megan",
    "Keith","Cheryl",
    "Christian","Andrea",
    "Roger","Hannah",
    "Noah","Martha",
    "Gerald","Jacqueline",
    "Carl","Frances",
    "Terry","Gloria",
    "Sean","Ann",
    "Austin","Teresa",
    "Arthur","Kathryn",
    "Lawrence","Sara",
    "Jesse","Janice",
    "Dylan","Jean",
    "Bryan","Alice",
    "Joe","Madison",
    "Jordan","Doris",
    "Billy","Abigail",
    "Bruce","Julia",
    "Albert","Judy",
    "Willie","Grace",
    "Gabriel","Denise",
    "Logan","Amber",
    "Alan","Marilyn",
    "Juan","Beverly",
    "Wayne","Danielle",
    "Roy","Theresa",
    "Ralph","Sophia",
    "Randy","Marie",
    "Eugene","Diana",
    "Vincent","Brittany",
    "Russell","Natalie",
    "Elijah","Isabella",
    "Louis","Charlotte",
    "Bobby","Rose",
    "Philip","Alexis",
    "Johnny","Kayla"
};
QStringList CoursesSource=
{
    "软件体系结构",
    "数据挖掘与R语言编程",
    "推荐系统",
    "深度学习与实践",
    "机器翻译",
    "医学影像智能处理技术",
    "专业外语(计算机)",
    "普适计算导论",
    "生物信息学导论",
    "计算机网络技术",
    "数据库管理系统实现技术",
    "Linux操作系统分析",
    "多媒体技术",
    "虚拟现实技术",
    "新技术专题",
    "计算机系统专题",
    "数据库系统实践",
    "工程项目管理",
    "数学建模技术",
    "Web编程技术",
    "Python编程与数据分析",
    "RFID射频识别技术",
    "计算机图形学",
    "系统开发平台及应用",
    "机器学习导论",
    "可视化程序设计技术及应用（双语）",
    "大数据算法",
    "移动开发技术",
    "嵌入式系统及其应用",
    "车联网技术与应用",
    "信息安全基础"
};

#endif // GENERATOR_H
