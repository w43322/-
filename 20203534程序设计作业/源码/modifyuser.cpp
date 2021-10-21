#include"modifyuser.h"

const int argumentCount=3;//按钮数量

void modifyUser::run()
{
    init();
    int cmd=modifyUserWindow.getCmd(argumentCount);
    processCmd(cmd);
}

void modifyUser::processCmd(int cmd)
{
    //获取输入框中的文字
    username.gettext(100,usernameStr);
    password.gettext(100,passwordStr);
    role.gettext(100,roleStr);
    deleted.gettext(100,deletedStr);
    fullname.gettext(100,fullnameStr);
    birthday.gettext(100,birthdayStr);
    sex.gettext(100,sexStr);
    email.gettext(100,emailStr);
    otherinfo.gettext(1000,otherinfoStr);
    //隐藏输入框
    username.visible(false);
    password.visible(false);
    role.visible(false);
    deleted.visible(false);
    fullname.visible(false);
    birthday.visible(false);
    sex.visible(false);
    email.visible(false);
    otherinfo.visible(false);

    switch(cmd)
    {
        case 0:
        {
            goBack();
            break;
        }
        case 1:
        {
            //检查用户名是否存在
            std::string whereStr;
            whereStr+="WHERE USERNAME = '";
            whereStr+=(std::string)usernameStr;
            whereStr+="'";
            dbLines line=userDatabase.selectRecords("USER",whereStr.c_str());
            int userROWID;
            int userprofileROWID;
            if(line.vec.size()==1)//如果存在
            {
                //弹窗提示
                modifyUserWindow.createPopup("User found.","OK");
                //选择并记录用户所在的行
                userROWID=line.vec[0];
                line=userDatabase.selectRecords("USERPROFILE",whereStr.c_str());
                userprofileROWID=line.vec[0];
            }
            else//如果不存在
            {
                //弹窗提示
                modifyUserWindow.createPopup("Creating new user.","OK");
                //创建新用户
                userDatabase.insertRecord("USER",1,"USERNAME",usernameStr);
                userDatabase.insertRecord("USERPROFILE",1,"USERNAME",usernameStr);
                //记录用户所在的行
                line=userDatabase.selectRecords("USER",whereStr.c_str());
                userROWID=line.vec[0];
                line=userDatabase.selectRecords("USERPROFILE",whereStr.c_str());
                userprofileROWID=line.vec[0];
            }
            //选择这个用户的记录
            dbRecord record=userDatabase.selectRecordByRowid("USER",userROWID);
            strcpy(passwordStr,record.mp["PASSWORD"].c_str());
            strcpy(roleStr,record.mp["ROLE"].c_str());
            strcpy(deletedStr,record.mp["DELETED"].c_str());
            //把信息复制到输入框
            record=userDatabase.selectRecordByRowid("USERPROFILE",userprofileROWID);
            strcpy(fullnameStr,record.mp["FULLNAME"].c_str());
            strcpy(birthdayStr,record.mp["BIRTHDAY"].c_str());
            strcpy(sexStr,record.mp["SEX"].c_str());
            strcpy(emailStr,record.mp["EMAIL"].c_str());
            strcpy(otherinfoStr,record.mp["OTHERINFO"].c_str());
            //调整输入框可见性
            username.visible(true);
            password.visible(true);
            role.visible(true);
            deleted.visible(true);
            fullname.visible(true);
            birthday.visible(true);
            sex.visible(true);
            email.visible(true);
            otherinfo.visible(true);

            run();
            break;
        }
        case 2:
        {
            //特判root用户
            if(strcmp(usernameStr,"username")==0)
            {
                modifyUserWindow.createPopup("Cannot update root.","OK");
            }
            else
            {
                //把用户信息写入数据库
                userDatabase.updateRecord(
                "USER","USERNAME"
                ,("'"+(std::string)usernameStr+"'").c_str()
                ,"PASSWORD"
                ,("'"+(std::string)passwordStr+"'").c_str());
                userDatabase.updateRecord(
                "USER","USERNAME"
                ,("'"+(std::string)usernameStr+"'").c_str()
                ,"ROLE"
                ,roleStr);
                userDatabase.updateRecord(
                "USER","USERNAME"
                ,("'"+(std::string)usernameStr+"'").c_str()
                ,"DELETED"
                ,deletedStr);
                //清空输入框
                userDatabase.updateRecord(
                "USERPROFILE","USERNAME"
                ,("'"+(std::string)usernameStr+"'").c_str()
                ,"FULLNAME"
                ,("'"+(std::string)fullnameStr+"'").c_str());
                userDatabase.updateRecord(
                "USERPROFILE","USERNAME"
                ,("'"+(std::string)usernameStr+"'").c_str()
                ,"BIRTHDAY"
                ,("'"+(std::string)birthdayStr+"'").c_str());
                userDatabase.updateRecord(
                "USERPROFILE","USERNAME"
                ,("'"+(std::string)usernameStr+"'").c_str()
                ,"SEX"
                ,("'"+(std::string)sexStr+"'").c_str());
                userDatabase.updateRecord(
                "USERPROFILE","USERNAME"
                ,("'"+(std::string)usernameStr+"'").c_str()
                ,"EMAIL"
                ,("'"+(std::string)emailStr+"'").c_str());
                userDatabase.updateRecord(
                "USERPROFILE","USERNAME"
                ,("'"+(std::string)usernameStr+"'").c_str()
                ,"OTHERINFO"
                ,("'"+(std::string)otherinfoStr+"'").c_str());
                //弹出按提示
                modifyUserWindow.createPopup("Update done.","OK");
            }
            //清空输入框
            strcpy(usernameStr,"");
            strcpy(passwordStr,"");
            strcpy(roleStr,"");
            strcpy(deletedStr,"");
            strcpy(fullnameStr,"");
            strcpy(birthdayStr,"");
            strcpy(sexStr,"");
            strcpy(emailStr,"");
            strcpy(otherinfoStr,"");
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

void modifyUser::goBack()
{
    //销毁输入框
    username.destroy();
    password.destroy();
    role.destroy();
    deleted.destroy();
    fullname.destroy();
    birthday.destroy();
    sex.destroy();
    email.destroy();
    otherinfo.destroy();

    userDatabase.closeDatabase();
    modifyUserWindow.close();
}

void modifyUser::init()
{
    userDatabase.openDatabase("users.db");
    strcpy(modifyUserWindow.imageSrc,"./bg/modifyuser");
    modifyUserWindow.init();
    modifyUserWindow.buttonOffsetX=modifyUserWindow.windowWidth*0.3;
    modifyUserWindow.drawButtons(argumentCount,"Back","Get/Create","Update Info");
    //绘制输入框
    modifyUserWindow.drawEditBox(&username
                                ,modifyUserWindow.windowWidth/2-100
                                ,250
                                ,200
                                ,30
                                ,usernameStr);
    modifyUserWindow.drawEditBox(&password
                                ,modifyUserWindow.windowWidth/2-100
                                ,250+35*1
                                ,200
                                ,30
                                ,passwordStr);
    modifyUserWindow.drawEditBox(&role
                                ,modifyUserWindow.windowWidth/2-100
                                ,250+35*2
                                ,200
                                ,30
                                ,roleStr);
    modifyUserWindow.drawEditBox(&deleted
                                ,modifyUserWindow.windowWidth/2-100
                                ,250+35*3
                                ,200
                                ,30
                                ,deletedStr);
    modifyUserWindow.drawEditBox(&fullname
                                ,modifyUserWindow.windowWidth/2-100
                                ,250+35*4
                                ,200
                                ,30
                                ,fullnameStr);
    modifyUserWindow.drawEditBox(&birthday
                                ,modifyUserWindow.windowWidth/2-100
                                ,250+35*5
                                ,200
                                ,30
                                ,birthdayStr);
    modifyUserWindow.drawEditBox(&sex
                                ,modifyUserWindow.windowWidth/2-100
                                ,250+35*6
                                ,200
                                ,30
                                ,sexStr);
    modifyUserWindow.drawEditBox(&email
                                ,modifyUserWindow.windowWidth/2-100
                                ,250+35*7
                                ,200
                                ,30
                                ,emailStr);
    modifyUserWindow.drawEditBox(&otherinfo
                                ,modifyUserWindow.windowWidth/2-100
                                ,250+35*8
                                ,200
                                ,30
                                ,otherinfoStr);


}
