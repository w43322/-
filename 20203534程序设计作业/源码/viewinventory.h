#ifndef VIEWINVENTORY_H_INCLUDED
#define VIEWINVENTORY_H_INCLUDED

#include<bits/stdc++.h>
#include"ui.h"
#include"db.h"

class viewInventory
{
    public:
        userInterface viewInventoryWindow;//用户界面
        dataBase inventoryDatabase;//数据库
        int nowPage=1,maxPage;//当前页和最后一页
        bool ONCE=0;//是否读取过数据库
        const int maxDisplay=15;//一页内显示的条目
        int recordCnt;//总条目数
        dbLines lines;//储存项目在数据库中的行号
        std::vector<dbRecord> records;//储存数据库中每一行数据
        void run();
        void processCmd(int);
        void goBack();
        void init();
};

#endif // VIEWINVENTORY_H_INCLUDED
