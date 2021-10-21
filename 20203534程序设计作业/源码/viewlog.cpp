#include"viewlog.h"

const int argumentCount=3;//��ť����

void viewLog::run()
{
    init();
    int cmd=viewLogWindow.getCmd(argumentCount);
    processCmd(cmd);
}

void viewLog::processCmd(int cmd)
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
            if(nowPage==1)//��һҳ
            {
                viewLogWindow.createPopup("Already 1st page!","OK");//��鵱ǰ�Ƿ��ڵ�һҳ
            }
            else
            {
                nowPage--;
            }
            run();
            break;
        }
        case 2://��һҳ
        {
            if(nowPage==maxPage)
            {
                viewLogWindow.createPopup("Already last page!","OK");//��鵱ǰ�Ƿ������һҳ
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

void viewLog::goBack()
{
    records.clear();
    logDatabase.closeDatabase();
    viewLogWindow.close();
}

void viewLog::init()
{
    logDatabase.openDatabase("log.db");
    strcpy(viewLogWindow.imageSrc,"./bg/viewlog");
    viewLogWindow.init();
    viewLogWindow.buttonOffsetX=viewLogWindow.windowWidth*0.3;
    viewLogWindow.drawButtons(argumentCount,"Back","Prev Page","Next Page");
    //Ϊ������Ч�ʣ�ֻ��ȡһ�����ݿ�
    if(0==ONCE)//����Ƿ��ǵ�һ������
    {
        //��ȡ���ݿ�
        lines=logDatabase.selectRecords("SELLLOG","");
        recordCnt=lines.vec.size();
        for(int i=0;i<recordCnt;i++)
            records.push_back(logDatabase.selectRecordByRowid("SELLLOG",lines.vec[i]));
        maxPage=recordCnt/maxDisplay+1;
        ONCE=1;
    }
    int Start=(nowPage-1)*maxDisplay;
    int End=(nowPage)*maxDisplay;
    //�Ѽ�¼�������Ļ
    int outtextY=100;
    setcolor(BLACK);
    setbkmode(TRANSPARENT);
    setfont(25,0,"Consolas");
    for(int i=Start;i<End&&i<recordCnt;i++,outtextY+=30)
    {
        char str2[100],str3[100];
        time_t TIME=atoll(records[i].mp.find("TIME")->second.c_str());
        char* str1=ctime(&TIME);
        int money=atoi(records[i].mp.find("MONEY")->second.c_str());
        sprintf(str2,"%d.%02d",money/100,money%100);
        sprintf(str3,"%s",records[i].mp.find("USER")->second.c_str());
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
