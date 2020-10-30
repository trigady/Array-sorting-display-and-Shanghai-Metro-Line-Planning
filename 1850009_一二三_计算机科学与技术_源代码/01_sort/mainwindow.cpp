#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //主页面的构造函数，用于设置一些基础布局、显示内容等
    ui->setupUi(this);

    this->setWindowTitle("1852979_01_sort");
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_released()
{
    //该按钮用于向子页面传入用户输入的信息

    //这里获取用户选择的排序方式
    sort_style=ui->choose_in->currentIndex();

    //这里先以QString的方式读入用户输入的全部文本，再转换为便于处理的char*数组
    QString qs=ui->num_in->toPlainText();
    char *qc = NULL;
    QByteArray ba = qs.toLatin1();
    qc = (char *)malloc(ba.length() + 1);
    memset(qc, 0, ba.length());
    memcpy(qc, ba.data(), ba.length());
    qc[ba.length()] = '\0';

    //这里用于注意读取用户输入的字符串
    long long temp = 0;
    bool flag=false;
    for(int i=0;i<ba.length();i++){
        if(qc[i]=='-'&&temp==0){
            flag=true;
        }else if(qc[i]>='0'&&qc[i]<='9'){
            temp=temp*10+(long long)(qc[i]-'0');
        }else if(qc[i]==' '){
            if(flag){
                temp=-temp;
            }
            the_num[the_len]=temp;
            the_len++;
            flag=false;
            temp=0;
        }else{
            //如果用户输入的信息非法，则不再读入，直接调用error窗口

            dsp=new re_dialog();
            dsp->show();

            ui->num_in->setMarkdown("");

            the_len=0;
            return;
        }

        if(i==ba.length()-1 && qc[i]!=' '){
            if(flag){
                temp=-temp;
            }
            the_num[the_len]=temp;
            the_len++;
        }
    }

    qDebug()<<sort_style;

    //构建子窗口，同时传入数据
    wsp=new subwindow(nullptr,sort_style,the_len,the_num);
    //保证子窗口可见
    wsp->show();

    //主窗口初始化
    the_len=0;
    ui->num_in->setMarkdown("");
    ui->choose_in->setCurrentIndex(0);
}
