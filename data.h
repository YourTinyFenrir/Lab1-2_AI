#ifndef DATA_H
#define DATA_H

#include "QVector"
#include "QHash"
#include "tree.h"
#include "field.h"

class Data {
    Tree tree;
    QVector<Node*> childrenForExpansion;
    QVector<Node*> newChildren;
    QVector<Node*> repeatingChildren;

    QHash<int, Node*> addedChildren;

    Field finalState;

    QString infoStr;
    int numOfSteps;
public:
    Data();

    void refresh(Node*);
    void setFS(Field);

    int getKey(Node*);
    QVector<Node*> getChildrenForExpansion();
    QVector<Node*> getNewChildren();
    QVector<Node*> getRepeatingChildren();
    QString getInfoStr();

    bool goalTest(Node*);
    QVector<Node*> getFinalResult();

    bool stepBlindSearch(QString);

};

#endif // DATA_H
