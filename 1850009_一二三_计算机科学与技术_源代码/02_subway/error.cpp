#include "error.h"
#include "ui_error.h"

//该文件用于构建报错页面，只需要显示对应布局即可

error::error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error)
{
    //构造函数，用于显示布局与其他内容的展示
    ui->setupUi(this);

    this->setWindowTitle("station wrong!");
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->width(), this->height());
}

error::~error()
{
    delete ui;
}

void error::on_pushButton_released()
{
    this->close();
}
