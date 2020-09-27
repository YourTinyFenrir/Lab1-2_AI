#ifndef DATA_H
#define DATA_H

#include "QVector"
#include "tree.h"
#include "field.h"

class Data {
    Tree tree;
    QVector<Node*> theOldestChildren;
    Field finalState;

    QVector<Field> content;
    int contentSize;

    int numOfNodes;
    int numOfSteps;
public:
    Data();

    void setTree(Field);
    void setFS(Field);

    Field getContent(int);
    int getContentSize();

    bool isComplete(Node*);
    void setResultToContent();

    bool stepBS();
    void blindSearch();
};

#endif // DATA_H
