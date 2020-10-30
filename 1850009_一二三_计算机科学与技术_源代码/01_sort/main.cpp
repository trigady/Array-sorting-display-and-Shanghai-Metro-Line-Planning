#include "mainwindow.h"

#include <QApplication>

//程序的开始入口
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
