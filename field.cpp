#include "field.h"
#include "qmath.h"

Field::Field() { }

Field::Field(QVector<int> num) {

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cell[i][j] = num[3*i + j];

}

Field::Field(Field* f) {

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            this->cell[i][j] = f->cell[i][j];

}

Field Field::switchCells(int n11, int n12, int n21, int n22) {

    Field f(*this);

    int num = f.cell[n11][n12];
    f.cell[n11][n12] = f.cell[n21][n22];
    f.cell[n21][n22] = num;

    return f;

}

int Field::toInt() {

    int res = 0;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            res += cell[i][j] * qPow(10, 3*i + j);

    return res;

}

QVector<Field> Field::possibleFields() {

    QVector<Field> res;

    bool isEnd = false;
    for (int i = 0; i < 3 && !isEnd; ++i)
        for (int j = 0; j < 3 && !isEnd; ++j) {
            if (cell[i][j] == 0) {
                if (i % 2 == 0 && j % 2 == 0) {
                    if (i == 0)
                        res.push_back(switchCells(0, j, 1, j));
                    else
                        res.push_back(switchCells(1, j, 2, j));
                    if (j == 0)
                        res.push_back(switchCells(i, 0, i, 1));
                    else
                        res.push_back(switchCells(i, 1, i, 2));
                }
                else if (i % 2 == 0 && j % 2 != 0) {
                    res.push_back(switchCells(1, 1, i, j));
                    if (i == 0) {
                        res.push_back(switchCells(0, 1, 0, 0));
                        res.push_back(switchCells(0, 1, 0, 2));
                    }
                    else {
                        res.push_back(switchCells(2, 1, 2, 0));
                        res.push_back(switchCells(2, 1, 2, 2));
                    }
                }
                else if (i % 2 != 0 && j % 2 == 0) {
                    res.push_back(switchCells(1, 1, i, j));
                    if (j == 0) {
                        res.push_back(switchCells(1, 0, 0, 0));
                        res.push_back(switchCells(1, 0, 2, 0));
                    }
                    else {
                        res.push_back(switchCells(2, 1, 0, 2));
                        res.push_back(switchCells(2, 1, 2, 2));
                    }
                }
                else {
                    res.push_back(switchCells(1, 1, 1, 0));
                    res.push_back(switchCells(1, 1, 0, 1));
                    res.push_back(switchCells(1, 1, 1, 2));
                    res.push_back(switchCells(1, 1, 2, 1));
                }
                isEnd = true;
            }
        }

    return res;

}
