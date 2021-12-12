#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qbigraph.h"
#include"generator.h"

#include<unordered_map>
#include<map>



QStringList Teachers;
QStringList Courses;
std::unordered_multimap<QString,QString>Link;

QBiGraph *QBG=NULL;
int TeacherCnt,CourseCnt;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->CourseCntLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->TeacherCntLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//--------------
void MainWindow::ClearTable()
{
    while(ui->TeacherTableWidget->rowCount())
            ui->TeacherTableWidget->removeRow(ui->TeacherTableWidget->rowCount()-1);
    while(ui->CourseTableWidget->rowCount())
            ui->CourseTableWidget->removeRow(ui->CourseTableWidget->rowCount()-1);
}
void MainWindow::DrawTable()
{
    ClearTable();
    for(auto it=Teachers.begin();it!=Teachers.end();++it)
    {
        auto &str=*it;
        int nowrow=ui->TeacherTableWidget->rowCount();
        ui->TeacherTableWidget->insertRow(nowrow);

        ui->TeacherTableWidget->setItem(nowrow,0,new QTableWidgetItem(str));
        ui->TeacherTableWidget->setItem(nowrow,1,new QTableWidgetItem(""));

        auto Range=Link.equal_range(str);
        for(auto p=Range.first;p!=Range.second;++p)
        {
            QTableWidgetItem *NowItem=ui->TeacherTableWidget->item(nowrow,1);
            QString nowstr=NowItem->text();
            NowItem->setText(nowstr+p->second+" ");
            //ui->TeacherTableWidget->setItem(nowrow,1,NowItem);
        }
    }
    for(auto it=Courses.begin();it!=Courses.end();++it)
    {
        auto &str=*it;
        int nowrow=ui->CourseTableWidget->rowCount();
        ui->CourseTableWidget->insertRow(nowrow);

        ui->CourseTableWidget->setItem(nowrow,0,new QTableWidgetItem(str));
    }
}
//--------------

void MainWindow::on_RandomPushButton_clicked()
{
    if(QBG)delete QBG;
    TeacherCnt=ui->TeacherCntLineEdit->text().toInt();
    CourseCnt=ui->CourseCntLineEdit->text().toInt();

    Teachers=RandomGenerate(TeachersSource,TeacherCnt);
    Courses=RandomGenerate(CoursesSource,CourseCnt);
    Link=RandomGenerateLink(Teachers,Courses);

    qDebug()<<TeacherCnt<<CourseCnt;

    QBG=new QBiGraph(Teachers,Courses,Link);

    QBG->show(ui->scrollAreaWidgetContents);

    DrawTable();
}


void MainWindow::on_RunDinicButton_clicked()
{
    QBG->RunDinic(ui->scrollAreaWidgetContents);
}

