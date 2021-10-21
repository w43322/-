#include"modifyuser.h"

const int argumentCount=3;//��ť����

void modifyUser::run()
{
    init();
    int cmd=modifyUserWindow.getCmd(argumentCount);
    processCmd(cmd);
}

void modifyUser::processCmd(int cmd)
{
    //��ȡ������е�����
    username.gettext(100,usernameStr);
    password.gettext(100,passwordStr);
    role.gettext(100,roleStr);
    deleted.gettext(100,deletedStr);
    fullname.gettext(100,fullnameStr);
    birthday.gettext(100,birthdayStr);
    sex.gettext(100,sexStr);
    email.gettext(100,emailStr);
    otherinfo.gettext(1000,otherinfoStr);
    //���������
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
            //����û����Ƿ����
            std::string whereStr;
            whereStr+="WHERE USERNAME = '";
            whereStr+=(std::string)usernameStr;
            whereStr+="'";
            dbLines line=userDatabase.selectRecords("USER",whereStr.c_str());
            int userROWID;
            int userprofileROWID;
            if(line.vec.size()==1)//�������
            {
                //������ʾ
                modifyUserWindow.createPopup("User found.","OK");
                //ѡ�񲢼�¼�û����ڵ���
                userROWID=line.vec[0];
                line=userDatabase.selectRecords("USERPROFILE",whereStr.c_str());
                userprofileROWID=line.vec[0];
            }
            else//���������
            {
                //������ʾ
                modifyUserWindow.createPopup("Creating new user.","OK");
                //�������û�
                userDatabase.insertRecord("USER",1,"USERNAME",usernameStr);
                userDatabase.insertRecord("USERPROFILE",1,"USERNAME",usernameStr);
                //��¼�û����ڵ���
                line=userDatabase.selectRecords("USER",whereStr.c_str());
                userROWID=line.vec[0];
                line=userDatabase.selectRecords("USERPROFILE",whereStr.c_str());
                userprofileROWID=line.vec[0];
            }
            //ѡ������û��ļ�¼
            dbRecord record=userDatabase.selectRecordByRowid("USER",userROWID);
            strcpy(passwordStr,record.mp["PASSWORD"].c_str());
            strcpy(roleStr,record.mp["ROLE"].c_str());
            strcpy(deletedStr,record.mp["DELETED"].c_str());
            //����Ϣ���Ƶ������
            record=userDatabase.selectRecordByRowid("USERPROFILE",userprofileROWID);
            strcpy(fullnameStr,record.mp["FULLNAME"].c_str());
            strcpy(birthdayStr,record.mp["BIRTHDAY"].c_str());
            strcpy(sexStr,record.mp["SEX"].c_str());
            strcpy(emailStr,record.mp["EMAIL"].c_str());
            strcpy(otherinfoStr,record.mp["OTHERINFO"].c_str());
            //���������ɼ���
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
            //����root�û�
            if(strcmp(usernameStr,"username")==0)
            {
                modifyUserWindow.createPopup("Cannot update root.","OK");
            }
            else
            {
                //���û���Ϣд�����ݿ�
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
                //��������
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
                //��������ʾ
                modifyUserWindow.createPopup("Update done.","OK");
            }
            //��������
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
    //���������
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
    //���������
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
