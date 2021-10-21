#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#include<bits/stdc++.h>
#include"ui.h"
#include"db.h"
#include"user.h"

#define LOGIN_SUCCESS 0
#define LOGIN_FAIL 1

#define LOGIN_ISADMIN 0
#define LOGIN_ISNOTADMIN 11

class logIn
{
    public:
        userInterface loginWindow;//用户界面
        sys_edit userName,passWord;//输入框
        dataBase userDataBase;//数据库
        char userNameStr[100],passWordStr[100];//用户名和密码
        void run();
        void processCmd(int);
        void goBack();
        void init();
        int checkPassWord(const char*,const char*);//检查密码
        int checkAdmin(const char*);//检查管理员
    private:
};

#endif // LOGIN_H_INCLUDED
