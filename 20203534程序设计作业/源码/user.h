#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include<bits/stdc++.h>
#include"ui.h"
#include"manage.h"
#include"registeritem.h"
#include"sell.h"

class User
{
    public:
        userInterface userWindow;//�û�����
        char userName[100];//�û���
        int admin=0;//�Ƿ����Ա
        void run();
        void processCmd(int);
        void goBack();
        void init();

    private:
};

#endif // USER_H_INCLUDED
