#ifndef MODIFYITEM_H_INCLUDED
#define MODIFYITEM_H_INCLUDED

#include<bits/stdc++.h>
#include"db.h"
#include"ui.h"

class modifyItem
{
    public:
        //�����
        sys_edit barcode,stock,pricein,priceout,name;
        sys_edit productprofile;

        dataBase itemDatabase;//���ݿ�

        //��Ʒ�ĸ�����Ϣ
        char barcodeStr[100]="";
        char stockStr[100]="";
        char priceinStr[100]="";
        char priceoutStr[100]="";
        char nameStr[100]="";
        char productprofileStr[1000]="";

        userInterface modifyItemWindow;//�û�����
        void run();
        void processCmd(int);
        void goBack();
        void init();

};

#endif // MODIFYITEM_H_INCLUDED
