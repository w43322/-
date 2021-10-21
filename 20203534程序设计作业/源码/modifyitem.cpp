#include"modifyitem.h"

const int argumentCount=3;//��ť����

void modifyItem::run()
{
    init();
    int cmd=modifyItemWindow.getCmd(argumentCount);
    processCmd(cmd);
}

void modifyItem::processCmd(int cmd)
{
    //��ȡ������е�����
    barcode.gettext(100,barcodeStr);
    stock.gettext(100,stockStr);
    pricein.gettext(100,priceinStr);
    priceout.gettext(100,priceoutStr);
    name.gettext(100,nameStr);
    productprofile.gettext(1000,productprofileStr);
    //���������
    barcode.visible(false);
    stock.visible(false);
    pricein.visible(false);
    priceout.visible(false);
    name.visible(false);
    productprofile.visible(false);
    switch(cmd)
    {
        case 0:
        {
            goBack();
            break;
        }
        case 1:
        {
            //�����Ʒ�����Ƿ����
            std::string whereStr;
            whereStr+="WHERE BARCODE = ";
            whereStr+=(std::string)barcodeStr;
            dbLines line=itemDatabase.selectRecords("PRODUCT",whereStr.c_str());
            int productROWID;
            int productprofileROWID;
            if(line.vec.size()==1)//�������
            {
                //������ʾ
                modifyItemWindow.createPopup("Item found.","OK");
                //ѡ�񲢼�¼��Ʒ���ڵ���
                productROWID=line.vec[0];
                line=itemDatabase.selectRecords("PRODUCTPROFILE",whereStr.c_str());
                productprofileROWID=line.vec[0];
            }
            else//���������
            {
                //������ʾ
                modifyItemWindow.createPopup("Creating new item.","OK");
                //��������Ʒ
                itemDatabase.insertRecord("PRODUCT",1,"BARCODE",barcodeStr);
                itemDatabase.insertRecord("PRODUCTPROFILE",1,"BARCODE",barcodeStr);
                //��¼��Ʒ���ڵ���
                line=itemDatabase.selectRecords("PRODUCT",whereStr.c_str());
                productROWID=line.vec[0];
                line=itemDatabase.selectRecords("PRODUCTPROFILE",whereStr.c_str());
                productprofileROWID=line.vec[0];
            }
            //ѡ�������Ʒ�ļ�¼
            dbRecord record=itemDatabase.selectRecordByRowid("PRODUCT",productROWID);
            //����Ϣ���Ƶ������
            strcpy(stockStr,record.mp["STOCK"].c_str());
            strcpy(priceinStr,record.mp["PRICEIN"].c_str());
            strcpy(priceoutStr,record.mp["PRICEOUT"].c_str());
            strcpy(nameStr,record.mp["NAME"].c_str());
            record=itemDatabase.selectRecordByRowid("PRODUCTPROFILE",productprofileROWID);
            strcpy(productprofileStr,record.mp["INFO"].c_str());
            //���������ɼ���
            stock.visible(true);
            pricein.visible(true);
            priceout.visible(true);
            name.visible(true);
            productprofile.visible(true);

            run();

            break;
        }
        case 2:
        {
            //��������е���Ϣ���µ����ݿ�
            itemDatabase.updateRecord(
            "PRODUCT","BARCODE",barcodeStr,"STOCK",stockStr);
            itemDatabase.updateRecord(
            "PRODUCT","BARCODE",barcodeStr,"PRICEIN",priceinStr);
            itemDatabase.updateRecord(
            "PRODUCT","BARCODE",barcodeStr,"PRICEOUT",priceoutStr);
            itemDatabase.updateRecord(
            "PRODUCT","BARCODE",barcodeStr,"NAME",
            ("'"+(std::string)nameStr+"'").c_str());
            itemDatabase.updateRecord(
            "PRODUCTPROFILE","BARCODE",barcodeStr,"INFO",
            ("'"+(std::string)productprofileStr+"'").c_str());
            //��������
            strcpy(barcodeStr,"");
            strcpy(stockStr,"");
            strcpy(priceinStr,"");
            strcpy(priceoutStr,"");
            strcpy(nameStr,"");
            strcpy(productprofileStr,"");
            //������ʾ
            modifyItemWindow.createPopup("Update done.","OK");

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

void modifyItem::goBack()
{
    //���������
    barcode.destroy();
    stock.destroy();
    pricein.destroy();
    priceout.destroy();
    name.destroy();
    productprofile.destroy();

    itemDatabase.closeDatabase();
    modifyItemWindow.close();
}

void modifyItem::init()
{
    itemDatabase.openDatabase("inventory.db");
    strcpy(modifyItemWindow.imageSrc,"./bg/modifyitem");
    modifyItemWindow.init();
    modifyItemWindow.buttonOffsetX=modifyItemWindow.windowWidth*0.3;
    //���ư�ť
    modifyItemWindow.drawButtons(argumentCount,"Back","Get/Create","Update Info");
    //���������
    modifyItemWindow.drawEditBox(&barcode
                                ,modifyItemWindow.windowWidth/2-100
                                ,250
                                ,200
                                ,30
                                ,barcodeStr);
    modifyItemWindow.drawEditBox(&stock
                                ,modifyItemWindow.windowWidth/2-100
                                ,250+35*1
                                ,200
                                ,30
                                ,stockStr);
    modifyItemWindow.drawEditBox(&pricein
                                ,modifyItemWindow.windowWidth/2-100
                                ,250+35*2
                                ,200
                                ,30
                                ,priceinStr);
    modifyItemWindow.drawEditBox(&priceout
                                ,modifyItemWindow.windowWidth/2-100
                                ,250+35*3
                                ,200
                                ,30
                                ,priceoutStr);
    modifyItemWindow.drawEditBox(&name
                                ,modifyItemWindow.windowWidth/2-100
                                ,250+35*4
                                ,200
                                ,30
                                ,nameStr);
    modifyItemWindow.drawEditBox(&productprofile
                                ,modifyItemWindow.windowWidth/2-100
                                ,250+35*5
                                ,200
                                ,30
                                ,productprofileStr);

}
