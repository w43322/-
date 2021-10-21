#ifndef SELL_H_INCLUDED
#define SELL_H_INCLUDED

#include<bits/stdc++.h>
#include"ui.h"
#include"db.h"

class Item//�����嵥�е�ÿһ����Ʒ
{
    public:
        std::string name;
        int price;
        int cnt;
};

class Sell
{
    public:
        userInterface sellWindow;//�û�����
        sys_edit barcode,itemCnt;//�����
        dataBase itemDatabase;//��Ʒ���ݿ�
        dataBase logDatabase;//��¼���ݿ�

        char userName[100];//�û���

        int sellMoneyTot=0;//���۶�

        std::map<std::string,Item>itemList;//�����嵥

        char barcodeStr[100];//����
        char itemCntStr[100];//��Ʒ��

        void run();
        void processCmd(int);
        void goBack();
        void init();

        void drawTable();//���Ʊ��

        void updateInventory();//���¿��

        void updateLog();//д���¼

    private:
};

#endif // SELL_H_INCLUDED
