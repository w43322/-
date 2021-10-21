#ifndef VIEWLOG_H_INCLUDED
#define VIEWLOG_H_INCLUDED

#include<bits/stdc++.h>
#include"ui.h"
#include"db.h"

class viewLog
{
    public:
        userInterface viewLogWindow;//�û�����
        dataBase logDatabase;//���ݿ�
        int nowPage=1,maxPage;//��ǰҳ�����һҳ
        bool ONCE=0;//�Ƿ��ȡ�����ݿ�
        const int maxDisplay=15;//һҳ����ʾ����Ŀ
        int recordCnt;//����Ŀ��
        dbLines lines;//������Ŀ�����ݿ��е��к�
        std::vector<dbRecord> records;//�������ݿ���ÿһ������
        void run();
        void processCmd(int);
        void goBack();
        void init();
};


#endif // VIEWLOG_H_INCLUDED
