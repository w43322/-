#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Cord
{
    int x,y;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void CallDrawTree(int);
    void DrawTree(void*,Cord,int);
    void Hide(void*);
private slots:
    #define BUTTONCLICKDECLEAR(n) void on_Button##n##_clicked();
    BUTTONCLICKDECLEAR(9)
    BUTTONCLICKDECLEAR(8)
    BUTTONCLICKDECLEAR(7)
    BUTTONCLICKDECLEAR(6)
    BUTTONCLICKDECLEAR(5)
    BUTTONCLICKDECLEAR(4)
    BUTTONCLICKDECLEAR(3)
    BUTTONCLICKDECLEAR(2)
    BUTTONCLICKDECLEAR(1)
    BUTTONCLICKDECLEAR(0)

    void on_ButtonBackSpace_clicked();

    void on_ButtonCLR_clicked();

    void on_ButtonInsert_clicked();

    void on_ButtonFind_clicked();

    void on_ButtonDelete_clicked();

    void on_ButtonNewTree_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_ButtonMergeTree_clicked();

    void on_ButtonDeleteTree_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
