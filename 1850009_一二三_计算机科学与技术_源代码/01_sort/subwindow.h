#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <vector>

namespace Ui {
class subwindow;
}

class subwindow : public QWidget
{
    Q_OBJECT

public:
    //这里的子页面构造函数因为要从主页面拿数据，所以采用传入构造参数的方式向子页面传递数据
    explicit subwindow(QWidget *parent = nullptr,int sort_style=0,int the_len=0,long long *the_num=nullptr);
    ~subwindow();

    //下列三个变量的含义与主页面中的相同
    int sort_style,the_len;
    long long the_num[1000];

    QVector<QString> the_out;       //这个vector用于存储每一步数组的变化情况
    int vec_index=0;                //vec_index用于记录用户当前查看的是第几步，便于记录

private slots:
    //分别对应三个按钮的槽函数
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

private:
    Ui::subwindow *ui;

    long long _old[1000],_cur[1000];

    QString get_qs(long long old[1000],long long current[1000]);
    void to_old();
    void init_old();

    //直接插入排序
    void one();

    //折半插入排序
    void two();

    //希尔排序
    void three();

    //冒泡排序
    void four();

    //快速排序
    void quick(int q, int p);
    void five();

    //简单选择排序
    void six();
};

#endif // SUBWINDOW_H
