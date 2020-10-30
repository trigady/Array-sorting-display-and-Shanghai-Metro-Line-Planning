#include "subwindow.h"
#include "ui_subwindow.h"
#include <QString>

subwindow::subwindow(QWidget *parent, int sort_style, int the_len, long long the_num[1000]) :
    QWidget(parent),
    ui(new Ui::subwindow)
{
    //次级窗口构造函数，显示布局
    ui->setupUi(this);

    this->setWindowTitle("sort_result");
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->width(), this->height());

    //对传入的信息进行保留记录
    this->sort_style = sort_style;
    this->the_len = the_len;
    for (int i = 0; i < the_len; i++) {
        this->the_num[i] = the_num[i];
    }

    //在文本框中提示当前选择的排序方式
    char title_qs[20];
    switch (sort_style) {
        case 0:
            qstrcpy(title_qs, "直接插入排序");
            one();
            break;
        case 1:
            qstrcpy(title_qs, "折半插入排序");
            two();
            break;
        case 2:
            qstrcpy(title_qs, "希尔排序");
            three();
            break;
        case 3:
            qstrcpy(title_qs, "冒泡排序");
            four();
            break;
        case 4:
            qstrcpy(title_qs, "快速排序");
            five();
            break;
        case 5:
            qstrcpy(title_qs, "简单选择排序");
            six();
            break;
    }

    //进行提示，注意中文编码要进行码值转换
    ui->out_title->setMarkdown(QString::fromLocal8Bit(title_qs) + ui->out_title->toPlainText());

    //首先展示用户输入的待排序数组
    QString qs;
    qs += QString::number(the_num[0]);
    for (int i = 1; i < the_len; i++) {
        qs = qs + ',' + QString::number(the_num[i]);
    }

    ui->out_text->setMarkdown(qs);
}

//该函数用于比较当前数组与前一阶段的状态差异，并返回标红处理后的字符串
QString subwindow::get_qs(long long *old, long long *current) {
    QString ans;
    bool flag = true;

    if (old[0] != current[0]) {
        flag = false;
        //利用标签布局方式对对应文本进行标红处理
        ans = ans + "<font color=red>" + QString::number(current[0]) + "</font>";
    }
    else {
        ans = ans + QString::number(current[0]);
    }
    for (int i = 1; i < the_len; i++) {
        if (old[i] != current[i]) {
            flag = false;
            ans = ans + "," + "<font color=red>" + QString::number(current[i]) + "</font>";
        }
        else {
            ans = ans + "," + QString::number(current[i]);
        }
    }

    //如果没有数字发生变化，不进行记录，返回NOT
    if (flag) {
        return "NOT";
    }

    return ans;
}

//用于让_old数组记录前一步状态
void subwindow::to_old() {
    for (int i = 0; i < the_len; i++) {
        _old[i] = _cur[i];
    }
}

//用于让_old和_cur都保持原始状态
void subwindow::init_old() {
    for (int i = 0; i < the_len; i++) {
        _old[i] = _cur[i] = the_num[i];
    }
}

//直接插入代码实现
void subwindow::one() {
    QString qs;
    int i,j;
    long long temp;

    init_old();

    for (i = 1; i < the_len; ++i){
        temp = _cur[i];

        for (j = i - 1; j >= 0; --j){
            if (temp < _cur[j]){
                _cur[j + 1] = _cur[j];
            }
            else { break; }
        }

        _cur[j + 1] = temp;

        qs = get_qs(_old, _cur);
        if (qs != "NOT") {
            the_out.push_back(qs);
            qs.clear();
            to_old();
        }
    }
}

//折半插入排序代码实现
void subwindow::two() {
    QString qs;
    int mid, low, high;
    long long temp;

    init_old();

    for (int i = 1; i < the_len; i++) {
        low = 0;
        high = i - 1;
        temp = _cur[i];

        while (low <= high) {
            mid = (low + high) / 2;
            if (_cur[i] < _cur[mid]) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }

        for (int j = i - 1; j >= high + 1; j--) {
            _cur[j + 1] = _cur[j];
        }

        _cur[high + 1] = temp;

        qs = get_qs(_old, _cur);
        if (qs != "NOT") {
            the_out.push_back(qs);
            qs.clear();
            to_old();
        }
    }
}

//希尔排序代码实现
void subwindow::three() {
    QString qs;
    const int the_gap = 2;              //这里我默认选用gap为2
    int j;
    long long temp;
    int gap = the_len / the_gap + 1;

    init_old();

    while (gap >= 1) {
        for (int i = gap; i < the_len; ++i) {
            temp = _cur[i];
            j = i;

            while (j >= gap && temp < _cur[j - gap]) {
                _cur[j] = _cur[j - gap];
                j -= gap;
            }

            _cur[j] = temp;

            qs = get_qs(_old, _cur);
            if (qs != "NOT") {
                the_out.push_back(qs);
                qs.clear();
                to_old();
            }
        }
        gap = gap / the_gap;
    }
}

//冒泡排序代码实现
void subwindow::four() {
    QString qs;
    long long temp;

    init_old();

    for (int i = the_len; i > 0; i--) {
        for (int j = 0; j < i - 1; j++) {
            if (_cur[j] > _cur[j + 1]) {
                temp = _cur[j];
                _cur[j] = _cur[j + 1];
                _cur[j + 1] = temp;

                qs = get_qs(_old, _cur);
                if (qs != "NOT") {
                    the_out.push_back(qs);
                    qs.clear();
                    to_old();
                }
            }
        }
    }
}

//快速排序代码实现
void subwindow::quick(int q, int p){
    QString qs;

    int i = q;
    int j = p;
    long long temp = _cur[i];

    if (i < j)
    {
        while (i < j)
        {
            while (i < j &&  _cur[j] >= temp)
                j--;
            if (i < j)
            {
                _cur[i] = _cur[j];
                i++;
            }

            while (i < j && temp > _cur[i])
                i++;
            if (i < j)
            {
                _cur[j] = _cur[i];
                j--;
            }

        }

        _cur[i] = temp;

        qs = get_qs(_old, _cur);
        if (qs != "NOT") {
            the_out.push_back(qs);
            qs.clear();
            to_old();
        }

        quick(q, i - 1);
        quick(i + 1, p);
    }
}

void subwindow::five() {
    init_old();

    quick(0,the_len-1);
}

//简单选择排序代码实现
void subwindow::six() {
    QString qs;
    int temp = 0;
    long long bios;

    init_old();

    for (int i = 0; i < the_len; i++) {
        temp = i;
        for (int j = i + 1; j < the_len; j++) {
            if (_cur[temp] > _cur[j]) {
                temp = j;
            }
        }
        if (temp != i) {
            bios = _cur[temp];
            _cur[temp] = _cur[i];
            _cur[i] = bios;
        }

        qs = get_qs(_old, _cur);
        if (qs != "NOT") {
            the_out.push_back(qs);
            qs.clear();
            to_old();
        }
    }
}

subwindow::~subwindow()
{
    delete ui;
}

//下一步按钮操作
void subwindow::on_pushButton_released()
{
    //到最后一步无法执行“下一步”操作
    if (vec_index == the_out.length()) {
        return;
    }
    ui->out_text->setMarkdown(the_out[vec_index]);
    vec_index++;
}

//多步至最后按钮操作
void subwindow::on_pushButton_2_released()
{
    //vec_index直接到最后一步
    vec_index = the_out.length() - 1;
    ui->out_text->setMarkdown(the_out[vec_index]);
    vec_index++;
}

//上一步按钮操作
void subwindow::on_pushButton_3_released()
{
    //在最开始无法进行上一部操作
    if (vec_index == 0) {
        return;
    }
    if (vec_index == 1) {
        vec_index = 0;
        QString qs;
        qs += QString::number(the_num[0]);
        for (int i = 1; i < the_len; i++) {
            qs = qs + ',' + QString::number(the_num[i]);
        }
        ui->out_text->setMarkdown(qs);
        return;
    }
    vec_index -= 2;
    ui->out_text->setMarkdown(the_out[vec_index]);
    vec_index++;
}
