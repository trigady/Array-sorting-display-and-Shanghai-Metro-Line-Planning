#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QColor>
#include <QColorDialog>
#include <vector>
#include <fstream>
#include <error.h>
#include "station.h"
#include "add_sta.h"
#include "add_way.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QVector<station> stations;
    QVector<subway_> sbs;

    path draw_it;

    int id_num = 0;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int is_in(std::string sp) {
            size_t uhi = stations.size();
            for (size_t i = 0; i < uhi; i++) {
                if (sp == stations[i].name) {
                    return i;
                }
            }
            return -1;
        }

        bool way_is_in(station sp, int subway) {
            for (size_t i = 0; i < sp.lines.size(); i++) {
                if (subway == sp.lines[i]) {
                    return true;
                }
            }
            return false;
        }

        bool sta_is_in(station sp, int sta_id) {
            for (size_t i = 0; i < sp.links.size(); i++) {
                if (sta_id == sp.links[i]) {
                    return true;
                }
            }
            return false;
        }

        int get_id(QString sp) {
            size_t temp = stations.size();
            for (size_t i = 0; i < temp; i++) {
                if (sp == QString::fromLocal8Bit((stations[i].name).data())) {
                    return i;
                }
            }
            return -1;
        }

        bool is_in_path(int id, path pth) {
            for (int i = 0; i < pth.times; i++) {
                if (id == pth.ids[i]) {
                    return true;
                }
            }
            return false;
        }


        void out_path(path pth);

        path search(int start, int end) {
            QVector<path> vec;
            path orig;
            orig.ids.push_back(start);
            orig.names.push_back(stations[start].name);
            orig.times = 1;
            vec.push_back(orig);

            path temp, tw;
            int num, bios, uhi;

            for (;;) {
                temp = vec[0];

                num = temp.ids[temp.ids.size() - 1];
                bios = stations[num].links.size();

                for (int i = 0; i < bios; i++) {
                    uhi = stations[num].links[i];
                    tw = temp;
                    if (uhi == end) {
                        tw.ids.push_back(uhi);
                        tw.names.push_back(stations[uhi].name);
                        tw.times++;
                        return tw;
                    }
                    if (!is_in_path(uhi, tw)) {
                        tw.ids.push_back(uhi);
                        tw.names.push_back(stations[uhi].name);
                        tw.times++;
                        for (;;) {
                            if (uhi == end) {
                                return tw;
                            }
                            if (stations[uhi].links.size() == 2) {
                                if (stations[uhi].links[0] != tw.ids[tw.ids.size() - 2]) {
                                    uhi = stations[uhi].links[0];
                                    tw.ids.push_back(uhi);
                                    tw.names.push_back(stations[uhi].name);
                                    tw.times++;
                                }
                                else if (stations[uhi].links[1] != tw.ids[tw.ids.size() - 2]) {
                                    uhi = stations[uhi].links[1];
                                    tw.ids.push_back(uhi);
                                    tw.names.push_back(stations[uhi].name);
                                    tw.times++;
                                }
                            }
                            else if (stations[uhi].links.size() == 1) {
                                break;
                            }
                            else {
                                vec.push_back(tw);
                                break;
                            }
                        }
                    }
                }

                vec.erase(vec.begin());
            }
        }


private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_released();
    void on_pushButton_2_released();
    void on_pushButton_3_released();
};

#endif // MAINWINDOW_H
