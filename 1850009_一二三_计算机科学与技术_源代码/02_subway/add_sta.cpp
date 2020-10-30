#include "add_sta.h"
#include "ui_add_sta.h"

//该文件主要用于站点的添加

add_sta::add_sta(QWidget *parent, QVector<station> *stas, int *idp) :
    QDialog(parent),
    ui(new Ui::add_sta)
{
    //添加站点的构造函数，显示布局并设置一些显示的内容
    ui->setupUi(this);

    this->setWindowTitle("Add new station");
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->width(), this->height());

    sts=stas;
    id_num=idp;
}

add_sta::~add_sta()
{
    delete ui;
}

//添加按钮的槽函数
void add_sta::on_pushButton_released()
{
    //用于以QString的方式获取用户输入的内容
    QString qs=ui->t_name->toPlainText();
    std::string qstr;

    //将用户获取的站点转化为索引值
    int a,b;
    qstr=std::string(qs.toLocal8Bit());
    station nst(qstr);

    a=(ui->t_x->toPlainText()).toInt();
    b=(ui->t_y->toPlainText()).toInt();

    //确定站点绘制位置
    nst.addr=QPoint(0.75*a,0.75*b);

    nst.id=*id_num;
    (*id_num)++;

    (*sts).push_back(nst);

    this->close();
}

void add_sta::on_pushButton_2_released()
{
    this->close();
}
