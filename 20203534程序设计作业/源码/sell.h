#ifndef SELL_H_INCLUDED
#define SELL_H_INCLUDED

#include<bits/stdc++.h>
#include"ui.h"
#include"db.h"

class Item//购物清单中的每一件商品
{
    public:
        std::string name;
        int price;
        int cnt;
};

class Sell
{
    public:
        userInterface sellWindow;//用户界面
        sys_edit barcode,itemCnt;//输入框
        dataBase itemDatabase;//商品数据库
        dataBase logDatabase;//记录数据库

        char userName[100];//用户名

        int sellMoneyTot=0;//销售额

        std::map<std::string,Item>itemList;//购物清单

        char barcodeStr[100];//条码
        char itemCntStr[100];//商品数

        void run();
        void processCmd(int);
        void goBack();
        void init();

        void drawTable();//绘制表格

        void updateInventory();//更新库存

        void updateLog();//写入记录

    private:
};

#endif // SELL_H_INCLUDED
