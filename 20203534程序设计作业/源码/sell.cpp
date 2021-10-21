#include"sell.h"
const int argumentCount=3;//��ť����

void Sell::run()
{
    init();
    int cmd=sellWindow.getCmd(argumentCount);
    processCmd(cmd);
}
void Sell::processCmd(int cmd)
{
    //��ȡ���������
    barcode.gettext(100,barcodeStr);
    itemCnt.gettext(100,itemCntStr);
    barcode.destroy();
    itemCnt.destroy();
    switch(cmd)
    {
        case 0:
        {
            goBack();
            break;
        }
        case 1:
        {
            //�������ݿ��������
            std::string whereStr;
            whereStr+="WHERE BARCODE = ";
            whereStr+=(std::string)barcodeStr;
            whereStr+="\n";
            //�ڿ���в�����Ʒ����
            dbLines rowid=itemDatabase.selectRecords("PRODUCT",whereStr.c_str());
            if(rowid.vec.size()==0)//���û�ҵ�������
            {
                sellWindow.createPopup("Item not found!","OK");
            }
            else
            {
                //����ҵ��ˣ�ѡ����Ʒ���ڵ���
                int ROWID=rowid.vec[0];
                dbRecord record=itemDatabase.selectRecordByRowid("PRODUCT",ROWID);
                //�ڹ����嵥�в�����Ʒ
                auto it=itemList.find(barcodeStr);
                if(it!=itemList.end())//����ҵ��������Ʒ����
                {
                    it->second.cnt+=atoi(itemCntStr);
                }
                else//���û�ҵ�������Ʒ��ӵ������嵥
                {
                    Item newitem;
                    newitem.name=record.mp["NAME"];
                    newitem.price=atoi(record.mp["PRICEOUT"].c_str());
                    newitem.cnt=atoi(itemCntStr);

                    itemList.insert(std::pair<std::string,Item>(barcodeStr,newitem));
                }
            }
            run();
            break;
        }
        case 2:
        {
            userInterface confirmSell;
            //�����µĽ���
            strcpy(confirmSell.imageSrc,"./bg/sell_proceed");
            int moneyCnt[8]={0,0,0,0,0,0,0,0};
            int moneyTot=0;

            COMMAND:

            confirmSell.init();
            confirmSell.buttonOffsetX=200;
            confirmSell.drawButtons(9,"100","50","20","10","5","1","0.5","0.1","Done");

            int outtextY=100;
            //������ʾ����
            //��ʾÿ����ֵ������
            for(int i=0;i<=7;i++,outtextY+=30)
            {
                char str[25];
                sprintf(str,"%d",moneyCnt[i]);
                setcolor(BLACK);
                setbkmode(TRANSPARENT);
                setfont(25,0,"Consolas");
                settextjustify(RIGHT_TEXT,TOP_TEXT);
                outtextxy(515,outtextY,str);
            }
            //��ʾ�����ܽ��
            char str[25];
            sprintf(str,"%d.%02d",sellMoneyTot/100,sellMoneyTot%100);
            setcolor(BLACK);
            setbkmode(TRANSPARENT);
            setfont(50,0,"Consolas");
            settextjustify(RIGHT_TEXT,TOP_TEXT);
            outtextxy(500,400,str);

            //��ʾʵ���տ���
            char str1[25];
            sprintf(str1,"%d.%02d",moneyTot/100,moneyTot%100);
            setcolor(BLACK);
            setbkmode(TRANSPARENT);
            setfont(50,0,"Consolas");
            settextjustify(RIGHT_TEXT,TOP_TEXT);
            outtextxy(500,455,str1);

            //��ʾ������
            char str2[25];
            if(moneyTot-sellMoneyTot>0)
                sprintf(str2,"%d.%02d",(moneyTot-sellMoneyTot)/100,(moneyTot-sellMoneyTot)%100);
            else
                sprintf(str2,"not enough");
            setcolor(BLACK);
            setbkmode(TRANSPARENT);
            setfont(50,0,"Consolas");
            settextjustify(RIGHT_TEXT,TOP_TEXT);
            outtextxy(500,510,str2);

            //�ȴ�ָ�һ��9����ť
            int cmd=confirmSell.getCmd(9);
            //������˳�Ʊ��ֵ�İ�ť
            if(cmd<=7)moneyCnt[cmd]++;
            switch(cmd)//����Ӧ��ֵ�����������ӣ�����ת����ͷλ��
            {
                case 0:
                    moneyTot+=10000;
                    goto COMMAND;
                case 1:
                    moneyTot+=5000;
                    goto COMMAND;
                case 2:
                    moneyTot+=2000;
                    goto COMMAND;
                case 3:
                    moneyTot+=1000;
                    goto COMMAND;
                case 4:
                    moneyTot+=500;
                    goto COMMAND;
                case 5:
                    moneyTot+=100;
                    goto COMMAND;
                case 6:
                    moneyTot+=50;
                    goto COMMAND;
                case 7:
                    moneyTot+=10;
                    goto COMMAND;
                case 8:
                    break;
                default:
                    break;
            }

            //������е����֤������"�ɽ�"��ť
            updateInventory();//���¿��
            updateLog();//�������ۼ�¼
            //������ʾ
            sellWindow.createPopup("Sell Made!","OK");
            //��β����
            itemList.clear();
            confirmSell.close();
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
void Sell::init()
{
    itemDatabase.openDatabase("inventory.db");
    logDatabase.openDatabase("log.db");
    strcpy(sellWindow.imageSrc,"./bg/sell");
    sellWindow.init();
    sellWindow.buttonOffsetX=sellWindow.windowWidth*0.3;
    sellWindow.buttonOffsetY=170;
    sellWindow.drawButtons(argumentCount,"Back","Add","Proceed");
    //���������
    sellWindow.drawEditBox(&barcode,
                                sellWindow.windowWidth*0.8-100,
                                sellWindow.windowHeight/2-30-5,
                                200,
                                30,
                                "");
    sellWindow.drawEditBox(&itemCnt,
                                sellWindow.windowWidth*0.8-100,
                                sellWindow.windowHeight/2+5,
                                200,
                                30,
                                "");
    drawTable();
}
void Sell::goBack()
{
    itemList.clear();
    barcode.destroy();
    itemCnt.destroy();
    itemDatabase.closeDatabase();
    logDatabase.closeDatabase();
    sellWindow.close();
}
void Sell::drawTable()//���Ʊ��
{
    sellMoneyTot=0;
    setcolor(BLACK);
    setbkmode(TRANSPARENT);
    setfont(25,0,"Consolas");

    int outtextY=100;
    //���������嵥������Ϣ��ӡ����Ļ��
    for(auto it=itemList.begin()
        ;it!=itemList.end()
        ;it++,outtextY+=30)
    {
        char str2[25],str3[25];
        sprintf(str2,"%d.%02d",it->second.price/100,it->second.price%100);
        sprintf(str3,"%d",it->second.cnt);
        settextjustify(LEFT_TEXT,TOP_TEXT);
        outtextxy(100,outtextY,it->second.name.c_str());
        settextjustify(RIGHT_TEXT,TOP_TEXT);
        outtextxy(500,outtextY,str2);
        outtextxy(700,outtextY,str3);
        sellMoneyTot+=it->second.cnt*it->second.price;
    }
    char str[25];
    setcolor(BLACK);
    setbkmode(TRANSPARENT);
    setfont(50,0,"Consolas");
    settextjustify(LEFT_TEXT,TOP_TEXT);
    sprintf(str,"%d.%02d",sellMoneyTot/100,sellMoneyTot%100);
    outtextxy(400,5,str);

}
void Sell::updateInventory()//���¿����Ϣ
{
    //���������嵥��������Ӧ��Ʒ�Ŀ��
    for(auto it=itemList.begin()
        ;it!=itemList.end()
        ;it++)
    {
        std::string barStr=it->first;
        std::string whereStr;
        whereStr+="WHERE BARCODE = ";
        whereStr+=barStr;
        dbLines line=itemDatabase.selectRecords("PRODUCT",whereStr.c_str());
        int ROWID=line.vec[0];
        dbRecord record=itemDatabase.selectRecordByRowid("PRODUCT",ROWID);
        int nowStock=atoi(record.mp["STOCK"].c_str());
        int newStock=nowStock-(it->second.cnt);
        char newStockStr[25];
        sprintf(newStockStr,"%d",newStock);
        itemDatabase.updateRecord("PRODUCT","BARCODE",barStr.c_str(),"STOCK",newStockStr);
    }

}
void Sell::updateLog()//����������־
{
    //��¼ʱ��
    time_t nowTime=time(0);
    char timeStr[25];
    char moneyStr[25];
    sprintf(timeStr,"%lld",nowTime);
    sprintf(moneyStr,"%d",sellMoneyTot);
    std::string usernameString="'"+(std::string)userName+"'";
    logDatabase.insertRecord("SELLLOG",3,"TIME","MONEY","USER",timeStr,moneyStr,usernameString.c_str());
}
