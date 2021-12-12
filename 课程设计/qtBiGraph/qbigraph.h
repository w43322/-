#ifndef QBIGRAPH_H
#define QBIGRAPH_H

#include"bigraph.h"

#include<QLabel>
#include<QDebug>
#include<QPainter>

#include<unordered_map>
#include<map>

//mac
#define unordered_multimap multimap
#define unordered_map map

const int ELEMWIDTH=60;
const int ELEMHEIGHT=30;
const int LINEHEIGHT=ELEMHEIGHT+40;
const int DISTWIDTH=ELEMWIDTH+40;

class NodeSet
{
private:
    std::unordered_map<QString,int>Index;
    std::vector<QLabel*>Lab;

public:
    std::pair<int,int> GetCord(int index)
    {
        return std::make_pair(Lab[index]->x(),Lab[index]->y());
    }
    void setLab(QWidget *par,int line,float offset)
    {
        int y=line*LINEHEIGHT;
        for(unsigned i=0;i<Lab.size();++i)
        {
            int x=(offset+i)*DISTWIDTH;
            Lab[i]->setParent(par);
            Lab[i]->setGeometry(x,y,ELEMWIDTH,ELEMHEIGHT);
            Lab[i]->show();
        }
        par->setMinimumWidth(std::max((int)(Lab.size()-1)*DISTWIDTH+ELEMWIDTH,par->minimumWidth()));
        par->setMinimumHeight(std::max(y+ELEMHEIGHT,par->minimumHeight()));
    }
    int size()
    {
        return Index.size();
    }
    void Add(const QString& str)
    {
        Index.insert(std::make_pair(str,size()));
        QLabel *LAB=new QLabel;
        LAB->setText(str);
        LAB->setStyleSheet("background-color: white; border: 2px solid red;\
                                        border-radius: "+QString::number(ELEMHEIGHT/2)+"px;\
                                        font-size: "+QString::number(ELEMHEIGHT/2)+"px;\
                                        color:red");
        LAB->setAlignment(Qt::AlignCenter);
        Lab.push_back(LAB);
    }
    ~NodeSet()
    {
        Index.clear();
        for(QLabel* i:Lab)
            delete i;
        Lab.clear();
    }
    int GetIndex(const QString &str)
    {
        auto res=Index.find(str);
        if(res==Index.end())
            return -1;
        else
            return res->second;
    }
};
class EdgeSet
{
private:
    std::unordered_multimap<int,int>Edges;
    QLabel *DrawingBoard;
    void _add(int u,int v)
    {
        Edges.insert(std::make_pair(u,v));
    }
public:
    void setlab(QWidget* par,NodeSet& set1,NodeSet& set2)
    {

        int X=par->minimumWidth(),Y=par->minimumHeight();
        QImage pix(X,Y,QImage::Format_ARGB32_Premultiplied);
        QPainter paint(&pix);
        //pix.fill(Qt::white);
        pix.fill(qRgba(0,0,0,0));
        paint.setPen(QPen(Qt::red,2));
        paint.setRenderHints(QPainter::Antialiasing);
        paint.setRenderHints(QPainter::HighQualityAntialiasing);
        paint.setRenderHints(QPainter::SmoothPixmapTransform);
        for(auto i:Edges)
        {
            int u=i.first,v=i.second;
            //qDebug("u:%d v:%d",u,v);
            std::pair<int,int>cord1=set1.GetCord(u);
            std::pair<int,int>cord2=set2.GetCord(v);
            //qDebug("X1:%d Y1:%d X2:%d Y2:%d",cord1.first,cord1.second,cord2.first,cord2.second);
            paint.drawLine(cord1.first+ELEMWIDTH/2,cord1.second+ELEMHEIGHT/2,
                           cord2.first+ELEMWIDTH/2,cord2.second+ELEMHEIGHT/2);
        }

        paint.end();

        DrawingBoard->setParent(par);
        DrawingBoard->setGeometry(0,0,X,Y);
        DrawingBoard->setPixmap(QPixmap::fromImage(pix));
        DrawingBoard->lower();
        DrawingBoard->show();
    }
    int size()
    {
        return Edges.size();
    }
    void AddEdge(int u,int v)
    {
        _add(u,v);
    }
    void update(BiGraph *BG,int mode)
    {
        qDebug("getting new edges");
        Edges=BG->GetEdges(mode);
    }
    EdgeSet()
    {
        DrawingBoard=new QLabel;
    }
    ~EdgeSet()
    {
        delete DrawingBoard;
        Edges.clear();
    }
};

class QBiGraph
{
private:

public:
    NodeSet Source,Sink;
    EdgeSet SourceEdge,SinkEdge;
    NodeSet Set1,Set2;
    EdgeSet Edges;
    BiGraph *BG;
    void RunDinic(QWidget *par)
    {
        int res=BG->dinic();
        qDebug()<<"res:"<<res;
        Edges.update(BG,1);
        SourceEdge.update(BG,0);
        SinkEdge.update(BG,2);

        //Edges.setlab(par,Set1,Set2);

        show(par);
    }
    void show(QWidget *par)
    {
        par->setMinimumHeight(0);
        par->setMinimumWidth(0);
        qDebug()<<"in show";

        Set1.setLab(par,1,//(Set1.size()!=std::max(Set1.size(),Set2.size()))*
                        (std::max(Set1.size(),Set2.size())-Set1.size())/2.0);
        Set2.setLab(par,2,//(Set2.size()!=std::max(Set1.size(),Set2.size()))*
                        (std::max(Set1.size(),Set2.size())-Set2.size())/2.0);
        Source.setLab(par,0,(std::max(Set1.size(),Set2.size())-1)/2.0);
        Sink.setLab(par,3,(std::max(Set1.size(),Set2.size())-1)/2.0);
        qDebug()<<"in show1";
        Edges.setlab(par,Set1,Set2);
        qDebug()<<"in show2";
        SourceEdge.setlab(par,Source,Set1);
        SinkEdge.setlab(par,Set2,Sink);
    }
    QBiGraph(QStringList QSL1,QStringList QSL2,std::unordered_multimap<QString,QString>LINK)
    {
        Source.Add("Source");
        Sink.Add("Sink");
        BG=new BiGraph(QSL1.size(),QSL2.size());
        for(QString str:QSL1)
        {
            SourceEdge.AddEdge(0,Set1.size());
            Set1.Add(str);
        }
        for(QString str:QSL2)
        {
            SinkEdge.AddEdge(Set2.size(),0);
            Set2.Add(str);
        }
        for(std::pair<QString,QString> p:LINK)
        {

            int u=Set1.GetIndex(p.first);
            int v=Set2.GetIndex(p.second);
            //qDebug("link between %d and %d",u,v);
            Edges.AddEdge(u,v);
            BG->AddEdge(u+1,v+1,1);
        }
    }
    ~QBiGraph()
    {
        delete BG;
    }
};



#endif // QBIGRAPH_H
