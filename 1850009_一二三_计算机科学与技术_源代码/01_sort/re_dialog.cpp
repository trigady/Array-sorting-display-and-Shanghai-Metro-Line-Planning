#include "re_dialog.h"
#include "ui_re_dialog.h"

re_dialog::re_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::re_dialog)
{
    //错误窗口构造函数，显示布局
    ui->setupUi(this);

    this->setWindowTitle("wrong!");
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->width(), this->height());
}

re_dialog::~re_dialog()
{
    delete ui;
}

void re_dialog::on_pushButton_released()
{
    this->close();
}
