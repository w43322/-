#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED

#include<sqlite3.h>
#include<bits/stdc++.h>

class dbLines//���ز�ѯ������ڵ��к�
{
    public:
        std::vector<int>vec;
};

class dbRecord//һ����¼�е���Ϣ�����������
{
    public:
        std::map<std::string,std::string>mp;
};

class dataBase
{
    public:
        sqlite3 *dbPointer;//���ݿ�ָ��
        char* errorMsg=0;//������Ϣ
        void openDatabase(const char*);//�����ݿ�
        void closeDatabase();//�ر����ݿ�
        void insertRecord(const char*,int,...);//�����¼
        dbLines selectRecords(const char*,const char*);//���Ҽ�¼�������к�
        dbRecord selectRecordByRowid(const char*,int);//�����к�ѡ������¼�����ؼ�¼����
        void updateRecord(const char*,const char*,const char*,const char*,const char*);
        //���¼�¼����
    private:
        static int selectRecordsCallback(void *lineList,int argc,char **argv,char **azColName)
        //���Ҽ�¼�Ļص�
        {
            printf("---select records callback func called---\n");
            ((dbLines*)lineList)->vec.push_back(atoi(argv[0]));
            printf("line id:%s\n",argv[0]);
            return 0;
        }
        static int selectRecordByRowidCallback(void *RecordMap,int argc,char **argv,char **azColName)
        //ѡ���¼�Ļص�
        {
            printf("--select record by rowid callback func called--\n");
            for(int i=0;i<argc;i++)
            {
                printf("colname:%s argv:%s\n",azColName[i],argv[i]);
                ((dbRecord*)RecordMap)->mp.insert(std::pair<std::string,std::string>(azColName[i],argv[i]));
            }
            return 0;
        }
};

#endif // DB_H_INCLUDED
