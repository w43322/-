#ifndef MODIFYITEM_H_INCLUDED
#define MODIFYITEM_H_INCLUDED

#include<bits/stdc++.h>
#include"db.h"
#include"ui.h"

class modifyItem
{
    public:
        //输入框
        sys_edit barcode,stock,pricein,priceout,name;
        sys_edit productprofile;

        dataBase itemDatabase;//数据库

        //商品的各项信息
        char barcodeStr[100]="";
        char stockStr[100]="";
        char priceinStr[100]="";
        char priceoutStr[100]="";
        char nameStr[100]="";
        char productprofileStr[1000]="";

        userInterface modifyItemWindow;//用户界面
        void run();
        void processCmd(int);
        void goBack();
        void init();

};

#endif // MODIFYITEM_H_INCLUDED
