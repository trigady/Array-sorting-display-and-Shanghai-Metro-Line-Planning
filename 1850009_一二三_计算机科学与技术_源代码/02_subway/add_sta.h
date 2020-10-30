#ifndef ADD_STA_H
#define ADD_STA_H

#include <QDialog>
#include "station.h"
#include "string"

//该头文件用于站点的添加

namespace Ui {
class add_sta;
}

class add_sta : public QDialog
{
    Q_OBJECT

public:
    explicit add_sta(QWidget *parent = nullptr,QVector<station> *stas=nullptr,int *idp=nullptr);
    ~add_sta();
    QVector<station>* sts;
    int* id_num;

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

private:
    Ui::add_sta *ui;
};

#endif // ADD_STA_H
