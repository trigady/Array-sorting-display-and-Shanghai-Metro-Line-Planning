#ifndef ERROR_H
#define ERROR_H

#include <QDialog>

namespace Ui {
class error;
}

class error : public QDialog
{
    Q_OBJECT

public:
    explicit error(QWidget *parent = nullptr);
    ~error();

private slots:
    void on_pushButton_released();

private:
    Ui::error *ui;
};

#endif // ERROR_H
