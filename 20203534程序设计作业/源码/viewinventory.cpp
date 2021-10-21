#include"viewinventory.h"

const int argumentCount=3;//按钮数量

void viewInventory::run()
{
    init();
    int cmd=viewInventoryWindow.getCmd(argumentCount);
    processCmd(cmd);
}

void viewInventory::processCmd(int cmd)
{
    switch(cmd)
    {
        case 0:
        {
            goBack();
            break;
        }
        case 1://上一页
        {
            if(nowPage==1)//检查当前是否在第一页
            {
                viewInventoryWindow.createPopup("Already 1st page!","OK");
            }
            else
            {
                nowPage--;
            }
            run();
            break;
        }
        case 2://下一页
        {
            if(nowPage==maxPage)//检查当前是否在最后一页
            {
                viewInventoryWindow.createPopup("Already last page!","OK");
            }
            else
            {
                nowPage++;
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
void viewInventory::goBack()
{
    records.clear();
    inventoryDatabase.closeDatabase();
    viewInventoryWindow.close();
}

void viewInventory::init()
{
    inventoryDatabase.openDatabase("inventory.db");
    strcpy(viewInventoryWindow.imageSrc,"./bg/viewinventory");
    viewInventoryWindow.init();
    viewInventoryWindow.buttonOffsetX=viewInventoryWindow.windowWidth*0.3;
    viewInventoryWindow.drawButtons(argumentCount,"Back","Prev Page","Next Page");
    //为了提升效率，只读取一次数据库
    if(0==ONCE)//检查是否是第一次运行
    {
        //读取数据库
        lines=inventoryDatabase.selectRecords("PRODUCT","");
        recordCnt=lines.vec.size();
        for(int i=0;i<recordCnt;i++)
            records.push_back(inventoryDatabase.selectRecordByRowid("PRODUCT",lines.vec[i]));
        maxPage=recordCnt/maxDisplay+1;
        ONCE=1;
    }
    int Start=(nowPage-1)*maxDisplay;
    int End=(nowPage)*maxDisplay;
    //把记录输出到屏幕
    int outtextY=100;
    setcolor(BLACK);
    setbkmode(TRANSPARENT);
    setfont(25,0,"Consolas");
    for(int i=Start;i<End&&i<recordCnt;i++,outtextY+=30)
    {
        char str1[100],str2[100],str3[100];
        sprintf(str1,"%s",records[i].mp.find("NAME")->second.c_str());
        sprintf(str2,"%s",records[i].mp.find("STOCK")->second.c_str());
        sprintf(str3,"%s",records[i].mp.find("BARCODE")->second.c_str());
        settextjustify(LEFT_TEXT,TOP_TEXT);
        outtextxy(100,outtextY,str1);
        settextjustify(RIGHT_TEXT,TOP_TEXT);
        outtextxy(500,outtextY,str2);
        outtextxy(700,outtextY,str3);
    }
    char str[100];
    sprintf(str,"%d %d",nowPage,maxPage);
    outtextxy(700,100+maxDisplay*30,str);
}
