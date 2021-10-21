#include"manage.h"
const int argumentCount=5;//按钮数量

void Manage::run()
{
    init();
    int cmd=manageWindow.getCmd(argumentCount);
    processCmd(cmd);
}
void Manage::processCmd(int cmd)
{
    switch(cmd)
    {
        case 0:
        {
            goBack();
            break;
        }
        case 1://商品管理
        {
            modifyItem runModifyItem;
            runModifyItem.run();
            run();
            break;
        }
        case 2://查看销售记录
        {
            viewLog runViewLog;
            runViewLog.run();
            run();
            break;
        }
        case 3://查看库存
        {
            viewInventory runViewInventory;
            runViewInventory.run();
            run();
            break;
        }
        case 4://用户管理
        {
            modifyUser runModifyUser;
            runModifyUser.run();
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
void Manage::goBack()
{
    manageWindow.close();
}
void Manage::init()
{
    strcpy(manageWindow.imageSrc,"./bg/manage");
    manageWindow.init();
    manageWindow.drawButtons(argumentCount,"Back","Modify Item","Sell Data","Inventory","Modify User");
}
