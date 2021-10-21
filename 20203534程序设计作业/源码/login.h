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
        userInterface loginWindow;//�û�����
        sys_edit userName,passWord;//�����
        dataBase userDataBase;//���ݿ�
        char userNameStr[100],passWordStr[100];//�û���������
        void run();
        void processCmd(int);
        void goBack();
        void init();
        int checkPassWord(const char*,const char*);//�������
        int checkAdmin(const char*);//������Ա
    private:
};

#endif // LOGIN_H_INCLUDED
