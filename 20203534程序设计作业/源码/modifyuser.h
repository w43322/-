#ifndef MODIFYUSER_H_INCLUDED
#define MODIFYUSER_H_INCLUDED

#include<bits/stdc++.h>
#include"db.h"
#include"ui.h"


class modifyUser
{
    public:
        //�����
        sys_edit username,password;
        sys_edit role,deleted,fullname,birthday,sex,email,otherinfo;

        dataBase userDatabase;//���ݿ�
        //�û��ĸ�����Ϣ
        char usernameStr[100]="";
        char passwordStr[100]="";
        char roleStr[100]="";
        char deletedStr[100]="";
        char fullnameStr[100]="";
        char birthdayStr[100]="";
        char sexStr[100]="";
        char emailStr[100]="";
        char otherinfoStr[1000]="";

        userInterface modifyUserWindow;//�û�����
        void run();
        void processCmd(int);
        void goBack();
        void init();
};

#endif // MODIFYUSER_H_INCLUDED
