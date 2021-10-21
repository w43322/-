#include"user.h"
const int argumentCount=4;//按钮数量

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
        case 1://添加商品库存
        {
            registerItem runRegisterItem;
            runRegisterItem.run();
            //went back here
            run();
            break;
        }
        case 2://进入销售页面
        {
            Sell runSell;
            strcpy(runSell.userName,userName);
            runSell.run();
            run();
            break;
        }
        case 3://进入管理页面
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
