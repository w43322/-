#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include<bits/stdc++.h>
#include<graphics.h>
#include<ege/sys_edit.h>


class userInterface;

class popUp//��������
{
    public:
    int popupWidth=320;//�������
    int popupHeight=240;//�����߶�

    int popupOffsetX=0;//����λ��Xƫ��
    int popupOffsetY=0;//����λ��Yƫ��

    void drawPopup(userInterface*);//���Ƶ���

    void getClick(userInterface*);//��ȡ���������

    const char* content;//������Ϣ

    const char* buttonText;//��ť��Ϣ

};

class userInterface//ͼ�ν���
{
    public:

        int windowWidth=1280;//���ڿ��
        int windowHeight=720;//���ڸ߶�

        int buttonOffsetX=0;//��ťXƫ��
        int buttonOffsetY=0;//��ťYƫ��

        PIMAGE backGround=newimage();//����

        char imageSrc[100]="./bg/main";//����·��

        void init();//��ʼ��

        void drawButtons(int,...);//���ư�ť

        void drawEditBox(sys_edit*,int,int,int,int,const char*);//���������

        void close();//�ر�

        int getCmd(int);//��ȡָ��

        void createPopup(const char*,const char*);//���Ƶ���

    private:

};


#endif // UI_H_INCLUDED
