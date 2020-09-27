#ifndef FIELD_H
#define FIELD_H

#include <QVector>

struct Field {
    int cell[3][3];

    Field();
    Field(QVector<int>);
    Field(Field*);
    QVector<Field> possibleFields();
    Field switchCells(int, int, int, int);
};

#endif // FIELD_H
