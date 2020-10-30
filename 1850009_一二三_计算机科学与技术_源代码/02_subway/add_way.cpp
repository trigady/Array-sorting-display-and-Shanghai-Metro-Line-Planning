#include "add_way.h"
#include "ui_add_way.h"

//该函数用于添加轨道线路

add_way::add_way(QWidget *parent,QVector<station>* sts,QVector<subway_>* sbs) :
    QDialog(parent),
    ui(new Ui::add_way)
{
    //建立轨道线的头函数，设置布局与一些其他显示内容
    ui->setupUi(this);

    this->setWindowTitle("Add new subway line");
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->width(), this->height());

    this->sbs=sbs;
    this->sts=sts;
}

add_way::~add_way()
{
    delete ui;
}

//确认按钮的槽函数
void add_way::on_pushButton_released()
{
    //新建一个 subway_类变量，开始新建地铁线
    subway_ nsy;
    //获取用户输入的站点索引值、地铁的编号
    int a=get_id(ui->t_start->toPlainText());
    int b=get_id(ui->t_end->toPlainText());
    int num=ui->t_num->toPlainText().toInt();

    //若用户输入错误，则弹出error窗口
    if(a==-1||b==-1){
        error* esp=new error;
        esp->show();
        if(a==-1){
            ui->t_start->setMarkdown("");
        }
        if(b==-1){
            ui->t_end->setMarkdown("");
        }
        return;
    }

    //开始构建地铁信息
    nsy.id=num;
    nsy.sts.push_back(a);
    nsy.sts.push_back(b);

    (*sts)[a].links.push_back(b);
    (*sts)[a].lines.push_back(num);
    (*sts)[b].links.push_back(a);
    (*sts)[b].lines.push_back(num);

    //压入地铁容器，新建地铁成功
    sbs->push_back(nsy);
    update();

    this->close();
}

void add_way::on_pushButton_2_released()
{
    this->close();
}
