#include"user.h"
const int argumentCount=4;//��ť����

void User::run()
{
    init();
    int cmd=userWindow.getCmd(argumentCount);
    processCmd(cmd);
}
void User::processCmd(int cmd)
{
    switch(cmd)
    {
        case 0:
        {
            goBack();
            break;
        }
        case 1://�����Ʒ���
        {
            registerItem runRegisterItem;
            runRegisterItem.run();
            //went back here
            run();
            break;
        }
        case 2://��������ҳ��
        {
            Sell runSell;
            strcpy(runSell.userName,userName);
            runSell.run();
            run();
            break;
        }
        case 3://�������ҳ��
        {
            if(1==admin)
            {
                Manage runManage;
                strcpy(runManage.userName,userName);
                runManage.run();
            }
            else
            {
                userWindow.createPopup("You're not an Admin.","OK");
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
void User::goBack()
{
    userWindow.close();
}
void User::init()
{
    strcpy(userWindow.imageSrc,"./bg/user");
    userWindow.init();
    userWindow.drawButtons(argumentCount,"Back","Add Item","Sell","Manage");
}
