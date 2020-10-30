#ifndef RE_DIALOG_H
#define RE_DIALOG_H

#include <QDialog>

namespace Ui {
class re_dialog;
}

class re_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit re_dialog(QWidget *parent = nullptr);
    ~re_dialog();

private slots:
    void on_pushButton_released();                  //关闭按钮槽函数

private:
    Ui::re_dialog *ui;
};

#endif // RE_DIALOG_H
