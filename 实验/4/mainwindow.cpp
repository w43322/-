#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QLabel>
#include<QCheckBox>
#include<QTableWidgetItem>
#include<QPainter>
#include "avltree.h"

#include<cmath>

int Displaying=-1;

std::vector<struct AVLNode*>TREE;

int D;
const int W=40,H=30;
const int LeafOffsetX=5;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    while(!TREE.empty())
    {
        auto root=*TREE.begin();
        while(root)
            root=deleteAVLNode(root,root->data,root);
        TREE.erase(TREE.begin());
    }
    delete ui;
}

void MainWindow::Hide(void *pt)
{
    AVLNode* now_node=(AVLNode*)pt;
    if(now_node!=NULL)
    {
        now_node->lab.hide();
        now_node->Llink.hide();
        now_node->Rlink.hide();
        Hide(now_node->left);
        Hide(now_node->right);
    }
}

void MainWindow::DrawTree(void *pt,Cord now_cord,int now_depth)
{
    AVLNode* now_node=(AVLNode*)pt;
    now_node->lab.setParent(ui->DrawingBoard);
    now_node->Llink.setParent(ui->DrawingBoard);
    now_node->Rlink.setParent(ui->DrawingBoard);
    now_node->Llink.lower();
    now_node->Rlink.lower();
    //now_node->lab.hide();
    now_node->lab.setText(QString::number(now_node->data));
    ui->DrawingBoard->setMinimumWidth(std::max(now_cord.x+W,ui->DrawingBoard->minimumWidth()));
    ui->DrawingBoard->setMinimumHeight(std::max(now_cord.y+H,ui->DrawingBoard->minimumHeight()));
    now_node->lab.setGeometry(now_cord.x,now_cord.y,W,H);
    now_node->lab.setStyleSheet("background-color: white; border: 2px solid red;\
                                border-radius: "+QString::number(H/2)+"px;\
                                font-size: "+QString::number(H/2)+"px;\
                                color:red");
    now_node->lab.setAlignment(Qt::AlignCenter);
    now_node->lab.show();

    if(now_node->left!=NULL)
    {
        Cord L;
        L.x=now_cord.x-0.5*(W+LeafOffsetX)*(pow(2,D-now_depth-1));
        //L.x-=LeafOffsetX*(D-now_depth);
        L.y=now_cord.y+2*H;

        int pix_w=(now_cord.x+0.5*W)-(L.x+0.5*W),pix_h=2*H;
        QImage pix(pix_w,pix_h,QImage::Format_ARGB32_Premultiplied);
        QPainter paint(&pix);
        //pix.fill(Qt::white);
        pix.fill(qRgba(0,0,0,0));
        paint.setPen(QPen(Qt::red,2));
        paint.setRenderHints(QPainter::Antialiasing);
        paint.setRenderHints(QPainter::HighQualityAntialiasing);
        paint.setRenderHints(QPainter::SmoothPixmapTransform);
        paint.drawLine(pix_w,0,0,pix_h);
        paint.end();

        now_node->Llink.setGeometry(L.x+0.5*W,now_cord.y+0.5*H,pix_w,pix_h);
        now_node->Llink.setPixmap(QPixmap::fromImage(pix));
        now_node->Llink.show();

        DrawTree(now_node->left,L,now_depth+1);
    }
    if(now_node->right!=NULL)
    {
        Cord R;
        R.x=now_cord.x+0.5*(W+LeafOffsetX)*(pow(2,D-now_depth-1));
        //R.x+=LeafOffsetX*(D-now_depth);
        R.y=now_cord.y+2*H;

        int pix_w=(R.x+0.5*W)-(now_cord.x+0.5*W),pix_h=2*H;
        QImage pix(pix_w,pix_h,QImage::Format_ARGB32_Premultiplied);
        QPainter paint(&pix);
        //pix.fill(Qt::white);
        pix.fill(qRgba(0,0,0,0));
        paint.setPen(QPen(Qt::red,2));
        paint.setRenderHints(QPainter::Antialiasing);
        paint.setRenderHints(QPainter::HighQualityAntialiasing);
        paint.setRenderHints(QPainter::SmoothPixmapTransform);
        paint.drawLine(0,0,pix_w,pix_h);
        paint.end();

        now_node->Rlink.setGeometry(now_cord.x+0.5*W,now_cord.y+0.5*H,pix_w,pix_h);
        now_node->Rlink.setPixmap(QPixmap::fromImage(pix));
        now_node->Rlink.show();

        DrawTree(now_node->right,R,now_depth+1);
    }

}

void MainWindow::CallDrawTree(int whichTree)
{
    D=calheight(TREE[whichTree]);
    qDebug()<<"tree height"<<D;
    int Xroot=0.5*(W+LeafOffsetX)*(pow(2,D-1)-1);
    Cord CordRoot;
    CordRoot.x=Xroot,CordRoot.y=0;
    if(Displaying!=-1)
    {
        qDebug()<<"hiding"<<TREE[Displaying];
        Hide(TREE[Displaying]);
        Displaying=-1;
    }
    DrawTree(TREE[whichTree],CordRoot,1);
    Displaying=whichTree;
    update();
}

#define BUTTONCLICKFUNC(n)\
void MainWindow::on_Button##n##_clicked()\
{\
    if((long long)ui->lcdNumber->intValue()*10+n<=1e9)\
        ui->lcdNumber->display(ui->lcdNumber->intValue()*10+n);\
}\

BUTTONCLICKFUNC(9)
BUTTONCLICKFUNC(8)
BUTTONCLICKFUNC(7)
BUTTONCLICKFUNC(6)
BUTTONCLICKFUNC(5)
BUTTONCLICKFUNC(4)
BUTTONCLICKFUNC(3)
BUTTONCLICKFUNC(2)
BUTTONCLICKFUNC(1)
BUTTONCLICKFUNC(0)

void MainWindow::on_ButtonBackSpace_clicked()
{
    ui->lcdNumber->display(ui->lcdNumber->intValue()/10);
}

void MainWindow::on_ButtonCLR_clicked()
{
    ui->lcdNumber->display(0);
}

void MainWindow::on_ButtonInsert_clicked()
{
    int x=ui->lcdNumber->intValue();
    qDebug()<<"Inserting:"<<endl<<"    "<<x;

    if(Displaying==-1)
    {
        qDebug()<<"no tree being displayed";
        on_ButtonCLR_clicked();
        return;
    }
    qDebug()<<"to tree"<<Displaying;
    TREE[Displaying]=insert(TREE[Displaying],x);

    ui->tableWidget->setItem(Displaying,2,new QTableWidgetItem(QString::number(TREE[Displaying]->data)));
    ui->tableWidget->setItem(Displaying,3,new QTableWidgetItem(QString::number((long long)TREE[Displaying],16)));

    CallDrawTree(Displaying);

    on_ButtonCLR_clicked();
}


void MainWindow::on_ButtonFind_clicked()
{
    int x=ui->lcdNumber->intValue();
    qDebug()<<"Looking For:"<<endl<<"    "<<x;

    if(Displaying==-1)
    {
        qDebug()<<"no tree being displayed";
        on_ButtonCLR_clicked();
        return;
    }
    AVLNode* res=FIND(TREE[Displaying],x);
    if(res==NULL)
    {
        qDebug()<<"not found";
        on_ButtonCLR_clicked();
        return;
    }
    else
    {
        CallDrawTree(Displaying);
        res->lab.setStyleSheet("background-color: yellow; border: 2px solid red;\
                                border-radius: "+QString::number(H/2)+"px;\
                                font-size: "+QString::number(H/2)+"px;\
                                color:red");
    }

    on_ButtonCLR_clicked();
}


void MainWindow::on_ButtonDelete_clicked()
{
    int x=ui->lcdNumber->intValue();
    qDebug()<<"Trying to Delete:"<<endl<<"    "<<x;

    if(Displaying==-1)
    {
        qDebug()<<"no tree being displayed";
        on_ButtonCLR_clicked();
        return;
    }

    if(FIND(TREE[Displaying],x)==NULL)
    {
        qDebug()<<"not found";
        on_ButtonCLR_clicked();
        return;
    }
    TREE[Displaying]=deleteAVLNode(TREE[Displaying],x,TREE[Displaying]);

    if(TREE[Displaying]!=NULL)
    {
        ui->tableWidget->setItem(Displaying,2,new QTableWidgetItem(QString::number(TREE[Displaying]->data)));
        ui->tableWidget->setItem(Displaying,3,new QTableWidgetItem(QString::number((long long)TREE[Displaying],16)));

        CallDrawTree(Displaying);
    }
    else
    {
        ui->tableWidget->removeRow(Displaying);
        TREE.erase(TREE.begin()+Displaying);
        for(int i=Displaying;i<(int)TREE.size();++i)
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(i)));
        Displaying=-1;
    }

    on_ButtonCLR_clicked();
}


void MainWindow::on_ButtonNewTree_clicked()
{
    int x=ui->lcdNumber->intValue();
    //qDebug()<<"New Tree:"<<endl<<"    "<<x;

    struct AVLNode *NewTree=NULL;
    NewTree=insert(NewTree,x);

    qDebug()<<"got new addr"<<NewTree;

    TREE.push_back(NewTree);

    ui->tableWidget->insertRow(TREE.size()-1);
    QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
    checkBoxItem->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(TREE.size()-1,0,checkBoxItem);
    //ui->tableWidget->setCellWidget(TREE.size()-1,0,new QCheckBox);
    ui->tableWidget->setItem(TREE.size()-1,1,new QTableWidgetItem(QString::number(TREE.size()-1)));
    ui->tableWidget->setItem(TREE.size()-1,2,new QTableWidgetItem(QString::number(NewTree->data)));
    ui->tableWidget->setItem(TREE.size()-1,3,new QTableWidgetItem(QString::number((long long)NewTree,16)));


    on_ButtonCLR_clicked();
}


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    CallDrawTree(row);
}

void MainWindow::on_ButtonMergeTree_clicked()
{
    qDebug()<<"merging trees";
    int FirstSelected=-1;
    for(int i=0;i<(int)TREE.size();++i)
    {
        if(ui->tableWidget->item(i,0)->checkState())
        {
            FirstSelected=i;
            break;
        }
    }
    if(FirstSelected==-1)
    {
        qDebug()<<"nothing selected!";
        return;
    }
    for(int i=FirstSelected+1;i<(int)TREE.size();++i)
    {
        if(!ui->tableWidget->item(i,0)->checkState())
            continue;
        qDebug()<<i<<"is going to be merged with"<<FirstSelected;
        while(TREE[i])
        {

            TREE[FirstSelected]=insert(TREE[FirstSelected],TREE[i]->data);
            TREE[i]=deleteAVLNode(TREE[i],TREE[i]->data,TREE[i]);

            ui->tableWidget->setItem(FirstSelected,2,new QTableWidgetItem(QString::number(TREE[FirstSelected]->data)));
            ui->tableWidget->setItem(FirstSelected,3,new QTableWidgetItem(QString::number((long long)TREE[FirstSelected],16)));

            CallDrawTree(FirstSelected);
        }
        TREE.erase(TREE.begin()+i);
        ui->tableWidget->removeRow(i);
        --i;
    }
}


void MainWindow::on_ButtonDeleteTree_clicked()
{
    qDebug()<<"deleting trees";
    for(int i=0;i<(int)TREE.size();++i)
    {
        if(!ui->tableWidget->item(i,0)->checkState())
            continue;
        if(Displaying!=-1)
        {
            qDebug()<<"hiding"<<TREE[Displaying];
            Hide(TREE[Displaying]);
            Displaying=-1;
        }
        qDebug()<<i<<"is going to be deleted";
        while(TREE[i])
            TREE[i]=deleteAVLNode(TREE[i],TREE[i]->data,TREE[i]);
        TREE.erase(TREE.begin()+i);
        ui->tableWidget->removeRow(i);
        --i;
    }
    for(int i=0;i<(int)TREE.size();++i)
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(i)));
}

