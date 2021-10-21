#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include<bits/stdc++.h>
#include<graphics.h>
#include<ege/sys_edit.h>


class userInterface;

class popUp//弹出窗口
{
    public:
    int popupWidth=320;//弹窗宽度
    int popupHeight=240;//弹窗高度

    int popupOffsetX=0;//弹窗位置X偏移
    int popupOffsetY=0;//弹窗位置Y偏移

    void drawPopup(userInterface*);//绘制弹窗

    void getClick(userInterface*);//获取鼠标点击动作

    const char* content;//内容信息

    const char* buttonText;//按钮信息

};

class userInterface//图形界面
{
    public:

        int windowWidth=1280;//窗口宽度
        int windowHeight=720;//窗口高度

        int buttonOffsetX=0;//按钮X偏移
        int buttonOffsetY=0;//按钮Y偏移

        PIMAGE backGround=newimage();//背景

        char imageSrc[100]="./bg/main";//背景路径

        void init();//初始化

        void drawButtons(int,...);//绘制按钮

        void drawEditBox(sys_edit*,int,int,int,int,const char*);//绘制输入框

        void close();//关闭

        int getCmd(int);//获取指令

        void createPopup(const char*,const char*);//绘制弹窗

    private:

};


#endif // UI_H_INCLUDED
