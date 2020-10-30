#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//这里是主窗口的头文件，用于导入其他窗口的头文件，同时也是main函数所指引的程序开始的起点

#include <QMainWindow>
#include "subwindow.h"
#include "re_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    long long the_num[1000];        //the_num用于存储用户输入的所有数据
    int the_len=0;                  //the_len表示用户输入数据的个数
    int sort_style=0;               //sort_style表示用户选择的排序方式

    subwindow *wsp;                 //定义了两个子页面指针，用于随时打开
    re_dialog *dsp;

private slots:
    void on_pushButton_released();  // 按钮槽函数

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
