#include"registeritem.h"
const int argumentCount=2;//按钮数量

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
            //获取输入框内容
            itemID.gettext(100,itemIDStr);
            itemCount.gettext(100,itemCountStr);
            itemID.destroy();
            itemCount.destroy();
            //尝试追加库存
            int addStockSuccess=addStock(itemIDStr,itemCountStr);
            //库存中找不到商品
            if(ADDSTOCK_ITEMNOTEXIST==addStockSuccess)
            {
                registerItemWindow.createPopup("Item not in Inventory!","OK");
            }
            //添加成功
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
    //绘制按钮
    registerItemWindow.drawButtons(argumentCount,"Back","Add");
    //绘制输入框
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
    int stockAdd=atoi(itemCountStr);//追加商品的数量
    std::string whereStr;//定义数据库查找条件
    whereStr+="WHERE BARCODE = ";
    whereStr+=(std::string)itemIDStr;
    whereStr+=" \n";
    dbLines rowid=registerItemDatabase.selectRecords("PRODUCT",whereStr.c_str());
    if(rowid.vec.size()==0)//如果没找到，返回错误
        return ADDSTOCK_ITEMNOTEXIST;
    //更新数据库中库存信息
    int ROWID=rowid.vec[0];
    dbRecord record=registerItemDatabase.selectRecordByRowid("PRODUCT",ROWID);
    int stockNow=atoi(record.mp["STOCK"].c_str());
    char str1[25],str2[25];
    itoa(ROWID,str1,10);
    itoa(stockNow+stockAdd,str2,10);
    registerItemDatabase.updateRecord("PRODUCT","ROWID",str1,"STOCK",str2);
    return ADDSTOCK_SUCESS;
}
