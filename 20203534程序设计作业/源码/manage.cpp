#include"manage.h"
const int argumentCount=5;//��ť����

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
        case 1://��Ʒ����
        {
            modifyItem runModifyItem;
            runModifyItem.run();
            run();
            break;
        }
        case 2://�鿴���ۼ�¼
        {
            viewLog runViewLog;
            runViewLog.run();
            run();
            break;
        }
        case 3://�鿴���
        {
            viewInventory runViewInventory;
            runViewInventory.run();
            run();
            break;
        }
        case 4://�û�����
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
