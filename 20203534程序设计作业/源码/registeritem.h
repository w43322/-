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
        userInterface registerItemWindow;//�û�����
        sys_edit itemID,itemCount;//�����
        dataBase registerItemDatabase;//���ݿ�

        char itemIDStr[100];//����
        char itemCountStr[100];//��Ʒ����

        void run();
        void processCmd(int);
        void goBack();
        void init();

        int addStock(const char*,const char*);//��ӿ��



    private:
};

#endif // REGISTERITEM_H_INCLUDED
