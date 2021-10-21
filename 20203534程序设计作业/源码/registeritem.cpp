#include"registeritem.h"
const int argumentCount=2;//��ť����

void registerItem::run()
{
    init();
    int cmd=registerItemWindow.getCmd(argumentCount);
    processCmd(cmd);
}
void registerItem::processCmd(int cmd)
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
            //��ȡ���������
            itemID.gettext(100,itemIDStr);
            itemCount.gettext(100,itemCountStr);
            itemID.destroy();
            itemCount.destroy();
            //����׷�ӿ��
            int addStockSuccess=addStock(itemIDStr,itemCountStr);
            //������Ҳ�����Ʒ
            if(ADDSTOCK_ITEMNOTEXIST==addStockSuccess)
            {
                registerItemWindow.createPopup("Item not in Inventory!","OK");
            }
            //��ӳɹ�
            else if(ADDSTOCK_SUCESS==addStockSuccess)
            {
                registerItemWindow.createPopup("Stock added!","OK");
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
void registerItem::goBack()
{
    itemID.destroy();
    itemCount.destroy();
    registerItemDatabase.closeDatabase();
    registerItemWindow.close();
}
void registerItem::init()
{
    registerItemDatabase.openDatabase("inventory.db");
    strcpy(registerItemWindow.imageSrc,"./bg/registeritem");
    registerItemWindow.init();
    registerItemWindow.buttonOffsetY=130;
    //���ư�ť
    registerItemWindow.drawButtons(argumentCount,"Back","Add");
    //���������
    registerItemWindow.drawEditBox(&itemID,
                                registerItemWindow.windowWidth/2-100,
                                registerItemWindow.windowHeight/2-30-5,
                                200,
                                30,
                                "");
    registerItemWindow.drawEditBox(&itemCount,
                                registerItemWindow.windowWidth/2-100,
                                registerItemWindow.windowHeight/2+5,
                                200,
                                30,
                                "");
}
int registerItem::addStock(const char* itemIDStr,const char* itemCountStr)
{
    int stockAdd=atoi(itemCountStr);//׷����Ʒ������
    std::string whereStr;//�������ݿ��������
    whereStr+="WHERE BARCODE = ";
    whereStr+=(std::string)itemIDStr;
    whereStr+=" \n";
    dbLines rowid=registerItemDatabase.selectRecords("PRODUCT",whereStr.c_str());
    if(rowid.vec.size()==0)//���û�ҵ������ش���
        return ADDSTOCK_ITEMNOTEXIST;
    //�������ݿ��п����Ϣ
    int ROWID=rowid.vec[0];
    dbRecord record=registerItemDatabase.selectRecordByRowid("PRODUCT",ROWID);
    int stockNow=atoi(record.mp["STOCK"].c_str());
    char str1[25],str2[25];
    itoa(ROWID,str1,10);
    itoa(stockNow+stockAdd,str2,10);
    registerItemDatabase.updateRecord("PRODUCT","ROWID",str1,"STOCK",str2);
    return ADDSTOCK_SUCESS;
}
