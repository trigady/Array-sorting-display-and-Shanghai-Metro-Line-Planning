#ifndef ADD_WAY_H
#define ADD_WAY_H

#include <QDialog>
#include "station.h"
#include "error.h"

namespace Ui {
class add_way;
}

class add_way : public QDialog
{
    Q_OBJECT

public:
    explicit add_way(QWidget *parent = nullptr,QVector<station>* sts = nullptr,QVector<subway_>* sbs = nullptr);
    ~add_way();
    QVector<station>* sts;
    QVector<subway_>* sbs;

    int get_id(QString sp) {
        size_t temp = sts->size();
        for (size_t i = 0; i < temp; i++) {
            if (sp == QString::fromLocal8Bit(((*sts)[i].name).data())) {
                return i;
            }
        }
        return -1;
    }

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

private:
    Ui::add_way *ui;
};

#endif // ADD_WAY_H
