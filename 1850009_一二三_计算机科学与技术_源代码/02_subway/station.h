#ifndef STATION_H
#define STATION_H

#include <QVector>
#include <string>

class station {
public:
    std::string name;
    QVector<int> lines;
    QVector<int> links;
    QPoint addr;
    int id = -1;
    station(std::string name) {
        this->name = name;
    }
};

class path {
public:
    QVector<int> ids;
    QVector<std::string> names;
    int times = 0;
};

class subway_{
public:
    int id;
    QVector<int> sts;
};

#endif // STATION_H
