#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED

#include<sqlite3.h>
#include<bits/stdc++.h>

class dbLines//返回查询结果所在的行号
{
    public:
        std::vector<int>vec;
};

class dbRecord//一条记录中的信息，标题和内容
{
    public:
        std::map<std::string,std::string>mp;
};

class dataBase
{
    public:
        sqlite3 *dbPointer;//数据库指针
        char* errorMsg=0;//错误信息
        void openDatabase(const char*);//打开数据库
        void closeDatabase();//关闭数据库
        void insertRecord(const char*,int,...);//插入记录
        dbLines selectRecords(const char*,const char*);//查找记录，返回行号
        dbRecord selectRecordByRowid(const char*,int);//根据行号选择单条记录，返回记录内容
        void updateRecord(const char*,const char*,const char*,const char*,const char*);
        //更新记录内容
    private:
        static int selectRecordsCallback(void *lineList,int argc,char **argv,char **azColName)
        //查找记录的回调
        {
            printf("---select records callback func called---\n");
            ((dbLines*)lineList)->vec.push_back(atoi(argv[0]));
            printf("line id:%s\n",argv[0]);
            return 0;
        }
        static int selectRecordByRowidCallback(void *RecordMap,int argc,char **argv,char **azColName)
        //选择记录的回调
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
