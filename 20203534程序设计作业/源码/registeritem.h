#ifndef REGISTERITEM_H_INCLUDED
#define REGISTERITEM_H_INCLUDED

#include<bits/stdc++.h>
#include"ui.h"
#include"db.h"

#define ADDSTOCK_SUCESS 0
#define ADDSTOCK_ITEMNOTEXIST 11

class registerItem
{
    public:
        userInterface registerItemWindow;//用户界面
        sys_edit itemID,itemCount;//输入框
        dataBase registerItemDatabase;//数据库

        char itemIDStr[100];//条码
        char itemCountStr[100];//商品数量

        void run();
        void processCmd(int);
        void goBack();
        void init();

        int addStock(const char*,const char*);//添加库存



    private:
};

#endif // REGISTERITEM_H_INCLUDED
