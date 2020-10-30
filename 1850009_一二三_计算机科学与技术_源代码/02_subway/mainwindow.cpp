#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

//该文件是本工程的核心文件，用于构建初始地铁线路图等

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //构造函数，首先显示布局
    ui->setupUi(this);

    this->setWindowTitle("1852979_02_Shanghaisubway");
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->width(), this->height());

    //首先定义出17条地铁线
    for(int i=0;i<17;i++){
        subway_ haha;
        sbs.push_back(haha);
    }

    //定义文本流文件，开始从subway_data.txt中读取地铁信息
            std::fstream fp;
            //打开文件
            fp.open("subway_data.txt");
            if (!fp.is_open()) {
                exit(-1);
            }

            std::string temp;
            int a, b, subway;
            station* sp;
            int lp;
            int ssp;

            //依次构建17条地铁线
            for (int uhi = 0; uhi < 17; uhi++) {

                //首先读入地铁列号
                fp >> subway;
                //保证首站没有上一站
                lp = -1;
                sbs[uhi].id=subway;

                for (;;) {
                    //读入站点名
                    fp >> temp;
                    //当读到终止符时完成当前地铁线的读入
                    if (temp == "#") {
                        break;
                    }
                    //读入站点坐标
                    fp >> a >> b;

                    //判断当前站点是否已经在已知站点库中
                    if ((ssp = is_in(temp)) == -1) {
                        //如果不在则新建一个站点
                        sp = new station(temp);
                        sp->id = id_num++;
                        sp->addr=QPoint(a*0.75,b*0.75);

                        //如果当前站点的经过路线中没有当前讨论的地铁线，则压入
                        if (!way_is_in(*sp, subway)) {
                            sp->lines.push_back(subway);
                        }

                        //如果存在上一站，则将上一站与这一站连接起来
                        if (lp != -1) {
                            if (!sta_is_in(stations[lp], sp->id)) {
                                stations[lp].links.push_back(sp->id);
                            }
                            if (!sta_is_in(*sp, lp)) {
                                sp->links.push_back(lp);
                            }
                        }

                        //当前站记录位上一站
                        lp = sp->id;

                        //压入所有地铁站的容器
                        stations.push_back(*sp);

                        //释放空间
                        delete sp;
                    }
                    else {
                        //如果已有该站，则对已存在的站点进行操作

                        //判断该站点是否已记录经过改路线地铁，没有则压入栈
                        if (!way_is_in(stations[ssp], subway)) {
                            stations[ssp].lines.push_back(subway);
                        }

                        //如果存在上一站，则将上一站与这一站连接起来
                        if (lp != -1) {
                            if (!sta_is_in(stations[lp], ssp)) {
                                stations[lp].links.push_back(ssp);
                            }
                            if (!sta_is_in(stations[ssp], lp)) {
                                stations[ssp].links.push_back(lp);
                            }
                        }
                        //当前站记录为上一站
                        lp = ssp;
                    }
                    sbs[uhi].sts.push_back(lp);
                }
            }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//该函数用于输出换乘路线
void MainWindow::out_path(path pth) {
        int temp = pth.times;
        QString qs;

        for (int i = 0; i < temp; i++) {
            //换行
            if (i != 0) {
                qs+="<p>";
                qs+="->";
                qs+="</p>";
            }
            //输出该站点的名称
            qs+="<p>"+QString::fromLocal8Bit((stations[pth.ids[i]].name).data());
            qs+="...........";

            //输出该站点被经过的所有地铁线
            for(int j=0;j<stations[pth.ids[i]].lines.size();j++){
                qs+=QString::number(stations[pth.ids[i]].lines[j])+QString::fromLocal8Bit(std::string("号线").data())+" ";
            }
            qs+="</p>";
        }

        //输出展示
        ui->t_out->setMarkdown(qs);
    }

//定义Qt绘画时间，随生命周期调用，用于绘制外框、地铁线路图、最优换乘路径
void MainWindow::paintEvent(QPaintEvent *)
{
    //定义画笔QPainter
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,4));
    painter.drawRect(20,20,1460,1460);

    //首先绘制所有的地铁路线,根据列车编号绘制颜色
    for(int i=0;i<sbs.size();i++){
        switch (sbs[i].id) {
            case 1:
            painter.setPen(QPen(QColor(237,0,35),2));
            break;
            case 2:
            painter.setPen(QPen(QColor(140,198,32),2));
            break;
            case 3:
            painter.setPen(QPen(QColor(255,221,1),2));
            break;
            case 4:
            painter.setPen(QPen(QColor(76,32,133),2));
            break;
            case 5:
            painter.setPen(QPen(QColor(154,71,154),2));
            break;
            case 6:
            painter.setPen(QPen(QColor(221,2,102),2));
            break;
            case 7:
            painter.setPen(QPen(QColor(238,107,4),2));
            break;
            case 8:
            painter.setPen(QPen(QColor(1,152,221),2));
            break;
            case 9:
            painter.setPen(QPen(QColor(138,205,239),2));
            break;
            case 10:
            painter.setPen(QPen(QColor(187,177,192),2));
            break;
            case 11:
            painter.setPen(QPen(QColor(135,17,34),2));
            break;
            case 12:
            painter.setPen(QPen(QColor(1,120,100),2));
            break;
            case 13:
            painter.setPen(QPen(QColor(239,152,190),2));
            break;
            case 16:
            painter.setPen(QPen(QColor(151,212,194),2));
            break;
            case 17:
            painter.setPen(QPen(QColor(187,119,104),2));
            break;
            default:
            painter.setPen(QPen(QColor(0,0,0),2));
            break;
        }

        //开始绘制
        int temp=(int)sbs[i].sts.size();
        for(int j=0;j<temp-1;j++){
            painter.drawLine(stations[sbs[i].sts[j]].addr,stations[sbs[i].sts[j+1]].addr);
        }
    }

    //然后绘制换乘路线，如果没有查询则不进行绘制
    int bios=draw_it.ids.size();
    painter.setPen(QPen(QColor(255,0,0),6));
    for(int j=0;j<bios-1;j++){
        painter.drawLine(stations[draw_it.ids[j]].addr,stations[draw_it.ids[j+1]].addr);
    }

    //然后绘制地铁站点，包括绘制站点位置与站点名称
    painter.setFont(QFont("楷体", 5));

    int temp=(int)stations.size();
    painter.setPen(QPen(Qt::gray,7));
    for(int i=0;i<temp;i++){
        painter.drawPoint(stations[i].addr);
    }

    //这里绘制地铁站名
    painter.setPen(QPen(Qt::black,7));
    for(int i=0;i<temp;i++){
        painter.drawText(stations[i].addr+QPoint(-5,15),QString::fromLocal8Bit((stations[i].name).data()));
    }
}

//开始查询槽函数
void MainWindow::on_pushButton_released()
{
    //获取初始站点与目的站点
    QString qs=ui->t_start->toPlainText();
    QString qs2=ui->t_end->toPlainText();

    if(get_id(qs)==-1||get_id(qs2)==-1){
        error* sp=new error;
        sp->show();
        if(get_id(qs)==-1){
            ui->t_start->setMarkdown("");
        }
        if(get_id(qs2)==-1){
            ui->t_end->setMarkdown("");
        }
        return;
    }

    //调用优化后的宽度优先搜索算法进行查找
    path ans=search(get_id(qs),get_id(qs2));

    draw_it=ans;
    out_path(ans);


    //更新绘制
    update();
}

void MainWindow::on_pushButton_2_released()
{
    add_sta *sp= new add_sta(nullptr,&stations,&id_num);
    sp->show();
}

void MainWindow::on_pushButton_3_released()
{
    add_way *wp=new add_way(nullptr,&stations,&sbs);
    wp->show();
}
