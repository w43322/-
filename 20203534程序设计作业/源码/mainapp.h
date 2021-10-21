#ifndef MAINAPP_H_INCLUDED
#define MAINAPP_H_INCLUDED

#include<bits/stdc++.h>
#include"ui.h"
#include"login.h"

class mainApp
{
    public:
        userInterface mainWindow;//用户界面
        void run();
        void processCmd(int cmd);
        void goBack();
        void login();
        void init();
    private:

};

#endif // MAINAPP_H_INCLUDED
