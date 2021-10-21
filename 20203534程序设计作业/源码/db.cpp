#include"db.h"

void dataBase::openDatabase(const char* fileName)//打开数据库
{
    sqlite3_open(fileName,&dbPointer);
}
void dataBase::closeDatabase()//关闭数据库
{
    sqlite3_close(dbPointer);
}

void dataBase::insertRecord(const char* tableName,int argc,...)//插入记录
{
    char* collumName[100];
    char* collumValue[100];
    va_list argv;
    va_start(argv,argc);
    for(int i=0;i<argc;i++)
        collumName[i]=va_arg(argv,char*);
    for(int i=0;i<argc;i++)
        collumValue[i]=va_arg(argv,char*);
    va_end(argv);
    std::string sqlCmd;
    sqlCmd+="INSERT INTO ";sqlCmd+=(std::string)tableName;sqlCmd+=" (";
    for(int i=0;i<argc;i++)
    {
        sqlCmd+=(std::string)collumName[i];if(i+1!=argc)sqlCmd+=",";
    }
    sqlCmd+=")\n";
    sqlCmd+="VALUES (";
    for(int i=0;i<argc;i++)
    {
        sqlCmd+=(std::string)collumValue[i];if(i+1!=argc)sqlCmd+=",";
    }
    sqlCmd+=");\n";

    printf("----insertRecordsCommands----\n%s-----\n",sqlCmd.c_str());

    sqlite3_exec(dbPointer,sqlCmd.c_str(),NULL,NULL,&errorMsg);
}
dbLines dataBase::selectRecords(const char* tableName,const char* whereStr="")//选择记录
{
    std::string sqlCmd;
    sqlCmd+="SELECT ";
    sqlCmd+="ROWID";
    sqlCmd+=" FROM ";
    sqlCmd+=(std::string)tableName;
    sqlCmd+=" ";
    sqlCmd+=(std::string)whereStr;
    sqlCmd+=" ";

    printf("---select cmd:---\n%s\n",sqlCmd.c_str());

    dbLines lineResult;

    sqlite3_exec(dbPointer,sqlCmd.c_str(),selectRecordsCallback,(void*)&lineResult,&errorMsg);

    return lineResult;
}
void dataBase::updateRecord(const char* tableName,const char* whereWhat,
            const char* isWhat,const char* changeWhat,const char* toWhat)
//更新记录
{

    std::string sqlCmd;

    sqlCmd+="UPDATE ";
    sqlCmd+=(std::string)tableName;
    sqlCmd+=" SET ";
    sqlCmd+=(std::string)changeWhat;
    sqlCmd+=" = ";
    sqlCmd+=(std::string)toWhat;
    sqlCmd+=" where ";
    sqlCmd+=(std::string)whereWhat;
    sqlCmd+=" = ";
    sqlCmd+=(std::string)isWhat;
    sqlCmd+="\n";

    printf("----\n%s-----\n",sqlCmd.c_str());

    sqlite3_exec(dbPointer,sqlCmd.c_str(),NULL,NULL,&errorMsg);
}

dbRecord dataBase::selectRecordByRowid(const char* tableName,int rowid)
//根据行号选择记录
{
    dbRecord resultRecord;
    std::string sqlCmd;
    char tmp[25];

    sqlCmd+="SELECT * FROM ";
    sqlCmd+=(std::string)tableName;
    sqlCmd+=" WHERE ROWID = ";
    itoa(rowid,tmp,10);
    sqlCmd+=(std::string)tmp;
    sqlCmd+=" \n";

    printf("---select record by rowid cmd---\n%s\n",sqlCmd.c_str());

    sqlite3_exec(dbPointer,sqlCmd.c_str(),selectRecordByRowidCallback,(void*)&resultRecord,&errorMsg);

    return resultRecord;
}
