#ifndef FIELD_H
#define FIELD_H

#include <QVector>

struct Field {
    int cell[3][3];

    Field();
    Field(QVector<int>);
    Field(Field*);
    Field switchCells(int, int, int, int);
    int toInt();
    int cellsOnIncorrectPosition(Field);
    int manhattanDistance(Field);
    QVector<Field> possibleFields();
};

#endif // FIELD_H
