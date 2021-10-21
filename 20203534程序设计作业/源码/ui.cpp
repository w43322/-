#include"ui.h"

void userInterface::init()//初始化
{
    printf("initializing ui\n");
    initgraph(windowWidth,windowHeight,0);
    setcaption("Sale Manager V1.0 by w43322@NEU");
    getimage(backGround,imageSrc);
    putimage(0,0,backGround);
}

void userInterface::drawButtons(int argc,...)//绘制按钮
{
    char *buttonName[100];
    int midHeight=windowHeight/2;
    int midWidth=windowWidth/2;
    int buttonHeight=60;
    int buttonWidth=200;
    int buttonInterval=20;
    int buttonTop;
    int buttonLeft=midWidth-buttonWidth/2;
    va_list argv;
    va_start(argv,argc);
    for(int i=0;i<argc;i++)
        buttonName[i]=va_arg(argv,char*);
    va_end(argv);
    if(argc%2==0)//if n==2,4,6,8...
    {
        buttonTop=midHeight-buttonInterval/2
                  -buttonHeight*(argc/2)-buttonInterval*(argc/2-1);
    }
    else//if n==1,3,5,7,9...
    {
        buttonTop=midHeight-buttonHeight/2
                  -buttonHeight*(argc/2)-buttonInterval*(argc/2);
    }
    buttonLeft+=buttonOffsetX;
    buttonTop+=buttonOffsetY;
    for(int i=0;i<argc;i++)
    {
        setfillcolor(RED);
        bar(buttonLeft,buttonTop,buttonLeft+buttonWidth,
            buttonTop+buttonHeight);

        setcolor(WHITE);
        setbkmode(TRANSPARENT);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        setfont(buttonHeight*0.6,0,"Algerian");
        xyprintf(buttonLeft+buttonWidth/2,buttonTop+buttonHeight/2
                 ,"%s",buttonName[i]);

        buttonTop+=buttonHeight+buttonInterval;
    }

}

void userInterface::close()//关闭图形界面
{
    delimage(backGround);
}

int userInterface::getCmd(int argc)//获取指令
{
    int midHeight=windowHeight/2;
    int midWidth=windowWidth/2;
    int buttonHeight=60;
    int buttonWidth=200;
    int buttonInterval=20;
    int buttonTop;
    if(argc%2==0)//if n==2,4,6,8...
    {
        buttonTop=midHeight-buttonInterval/2
                  -buttonHeight*(argc/2)-buttonInterval*(argc/2-1);
    }
    else//if n==1,3,5,7,9...
    {
        buttonTop=midHeight-buttonHeight/2
                  -buttonHeight*(argc/2)-buttonInterval*(argc/2);
    }
    for(;is_run();delay_fps(60))
    {
        bool is_click=false;
        int x_click=0,y_click=0;
		mouse_msg msg={0};
        if(argc%2==0)//if n==2,4,6,8...
        {
            buttonTop=midHeight-buttonInterval/2
                      -buttonHeight*(argc/2)-buttonInterval*(argc/2-1);
        }
        else//if n==1,3,5,7,9...
        {
            buttonTop=midHeight-buttonHeight/2
                      -buttonHeight*(argc/2)-buttonInterval*(argc/2);
        }
		while(mousemsg())
		{
            msg=getmouse();
            if(msg.is_left()&&msg.is_down())
            {
				is_click=true;
				x_click=msg.x;
				y_click=msg.y;
			}
			if(is_click)
			{
                if(x_click>=buttonOffsetX+midWidth-buttonWidth/2&&x_click<=buttonOffsetX+midWidth+buttonWidth/2)
                {
                    for(int i=0;i<argc;i++,buttonTop+=buttonHeight+buttonInterval)
                    {
                        if(y_click>=buttonOffsetY+buttonTop&&y_click<=buttonOffsetY+buttonTop+buttonHeight)
                        {
                            return i;
                        }
                    }
                }
			}
			is_click=false;
        }
	}
    return 0;
}

void userInterface::drawEditBox(sys_edit* editBox,int x,int y,
                    int width,int height,const char* setText)
//绘制输入框
{
	editBox->create(false);
	editBox->size(width,height+8);
	editBox->setbgcolor(YELLOW);
	editBox->setfont(24,0,"Consolas");
	editBox->move(x,y);
	editBox->visible(true);
	editBox->settext(setText);
}

void userInterface::createPopup(const char* content,const char* buttonText)
//绘制弹窗
{
    popUp newpopup;
    newpopup.content=content;
    newpopup.buttonText=buttonText;
    newpopup.drawPopup(this);
    newpopup.getClick(this);
}

void popUp::drawPopup(userInterface* ui)
{
    int midHeight=ui->windowHeight/2;
    int midWidth=ui->windowWidth/2;

    int popupTop=midHeight-popupHeight/2;
    int popupLeft=midWidth-popupWidth/2;

    setfillcolor(WHITE);
    bar(popupLeft,popupTop,popupLeft+popupWidth,
        popupTop+popupHeight);

    setcolor(BLACK);
    line(popupLeft,popupTop
        ,popupLeft+popupWidth,popupTop);
    line(popupLeft,popupTop+popupHeight
        ,popupLeft+popupWidth,popupTop+popupHeight);
    line(popupLeft,popupTop
        ,popupLeft,popupTop+popupHeight);
    line(popupLeft+popupWidth,popupTop
        ,popupLeft+popupWidth,popupTop+popupHeight);

    setcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    setfont(30,0,"Algerian");
    xyprintf(popupLeft+popupWidth/2,popupTop+popupHeight*0.35
             ,"%s",content);

    setfillcolor(BLACK);
    bar(popupLeft+popupWidth/2-80
        ,popupTop+popupHeight*0.7-20
        ,popupLeft+popupWidth/2+80
        ,popupTop+popupHeight*0.7+20);

    setcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    setfont(30,0,"Algerian");
    xyprintf(popupLeft+popupWidth/2,popupTop+popupHeight*0.7
             ,"%s",buttonText);
}

void popUp::getClick(userInterface* ui)
{
    int midHeight=ui->windowHeight/2;
    int midWidth=ui->windowWidth/2;

    int popupTop=midHeight-popupHeight/2;
    int popupLeft=midWidth-popupWidth/2;

    for(;is_run();delay_fps(60))
    {
        bool is_click=false;
        int x_click=0,y_click=0;
		mouse_msg msg={0};
		while(mousemsg())
		{
            msg=getmouse();
            if(msg.is_left()&&msg.is_down())
            {
				is_click=true;
				x_click=msg.x;
				y_click=msg.y;
			}
			if(is_click)
			{
                if(x_click>=popupLeft+popupWidth/2-80&&x_click<=popupLeft+popupWidth/2+80)
                {
                    if(y_click>=popupTop+popupHeight*0.7-20&&y_click<=popupTop+popupHeight*0.7+20)
                    {
                        return;
                    }
                }
			}
			is_click=false;
        }
	}
}
