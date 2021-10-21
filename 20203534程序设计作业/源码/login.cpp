#include"login.h"
const int argumentCount=2;//��ť����

void logIn::run()
{
    init();
    int cmd=loginWindow.getCmd(argumentCount);
    processCmd(cmd);
}
void logIn::processCmd(int cmd)
{
    switch(cmd)
    {
        case 0:
        {
            goBack();
            break;
        }
        case 1:
        {
            //��ȡ�ı����е�����
            userName.gettext(100,userNameStr);
            passWord.gettext(100,passWordStr);
            userName.destroy();
            passWord.destroy();
            //����û���������
            int loginSuccess=checkPassWord(userNameStr,passWordStr);
            //����Ƿ����Ա
            int isAdmin=checkAdmin(userNameStr);
            //�����½�ɹ�
            if(LOGIN_SUCCESS==loginSuccess)
            {
                //�����û���������
                User runUser;
                //�����û���
                strcpy(runUser.userName,userNameStr);
                //����ǹ���Ա
                if(LOGIN_ISADMIN==isAdmin)
                    runUser.admin=1;
                //������ӭ
                loginWindow.createPopup(("Hello, "+(std::string)userNameStr).c_str(),"Welcome");
                //�����û���������
                runUser.run();
            }
            else
            {
                //��ʾ��¼ʧ��
                loginWindow.createPopup("Login Failed.","OK");
            }
            run();
            break;
        }
        default:
        {
            goBack();
            break;
        }
    }
}
void logIn::goBack()
{
    userName.destroy();
    passWord.destroy();
    userDataBase.closeDatabase();
    loginWindow.close();
}
void logIn::init()
{
    userDataBase.openDatabase("users.db");
    strcpy(loginWindow.imageSrc,"./bg/login");
    loginWindow.init();
    loginWindow.buttonOffsetY=130;
    //���ư�ť
    loginWindow.drawButtons(argumentCount,"Back","Go");
    //���������
    loginWindow.drawEditBox(&userName,
                            loginWindow.windowWidth/2-100,
                            loginWindow.windowHeight/2-30-5,
                            200,
                            30,
                            "");
    loginWindow.drawEditBox(&passWord,
                            loginWindow.windowWidth/2-100,
                            loginWindow.windowHeight/2+5,
                            200,
                            30,
                            "");
}
int logIn::checkPassWord(const char* username,const char* password)
//����û���������
{
    std::string whereStr;//���ݿ�Ĳ�ѯָ��
    whereStr+="WHERE DELETED = 0 AND USERNAME = '";
    whereStr+=(std::string)username;
    whereStr+="' AND PASSWORD = '";
    whereStr+=(std::string)password;
    whereStr+="'\n";
    dbLines resRowid=userDataBase.selectRecords("USER",whereStr.c_str());
    if(resRowid.vec.size())
        return LOGIN_SUCCESS;
    else
        return LOGIN_FAIL;
}
int logIn::checkAdmin(const char* username)
//����Ƿ����Ա
{
    std::string whereStr;
    whereStr+="WHERE USERNAME = '";
    whereStr+=(std::string)username;
    whereStr+="' AND ROLE = 1\n";
    dbLines resRowid=userDataBase.selectRecords("USER",whereStr.c_str());
    if(resRowid.vec.size())
        return LOGIN_ISADMIN;
    else
        return LOGIN_ISNOTADMIN;
}
