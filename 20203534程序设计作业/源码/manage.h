#ifndef MANAGE_H_INCLUDED
#define MANAGE_H_INCLUDED

#include<bits/stdc++.h>
#include"ui.h"
#include"modifyitem.h"
#include"modifyuser.h"
#include"viewlog.h"
#include"viewinventory.h"

class Manage
{
    public:
        userInterface manageWindow;//�û�����
        char userName[100];//�û���
        void run();
        void processCmd(int);
        void goBack();
        void init();

    private:
};

#endif // MANAGE_H_INCLUDED
