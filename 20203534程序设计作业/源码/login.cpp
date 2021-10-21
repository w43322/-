#include"login.h"
const int argumentCount=2;//按钮数量

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
            //获取文本框中的内容
            userName.gettext(100,userNameStr);
            passWord.gettext(100,passWordStr);
            userName.destroy();
            passWord.destroy();
            //检查用户名和密码
            int loginSuccess=checkPassWord(userNameStr,passWordStr);
            //检查是否管理员
            int isAdmin=checkAdmin(userNameStr);
            //如果登陆成功
            if(LOGIN_SUCCESS==loginSuccess)
            {
                //声明用户操作界面
                User runUser;
                //传递用户名
                strcpy(runUser.userName,userNameStr);
                //如果是管理员
                if(LOGIN_ISADMIN==isAdmin)
                    runUser.admin=1;
                //弹窗欢迎
                loginWindow.createPopup(("Hello, "+(std::string)userNameStr).c_str(),"Welcome");
                //运行用户操作界面
                runUser.run();
            }
            else
            {
                //提示登录失败
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
    //绘制按钮
    loginWindow.drawButtons(argumentCount,"Back","Go");
    //绘制输入框
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
//检查用户名和密码
{
    std::string whereStr;//数据库的查询指令
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
//检查是否管理员
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
