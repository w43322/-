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
        userInterface userWindow;//用户界面
        char userName[100];//用户名
        int admin=0;//是否管理员
        void run();
        void processCmd(int);
        void goBack();
        void init();

    private:
};

#endif // USER_H_INCLUDED
