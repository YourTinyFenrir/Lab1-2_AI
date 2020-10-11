#ifndef TREE_H
#define TREE_H

#include "field.h"

struct Node {
    Field content;
    QVector<Node*> children;
    int generation;
    Node* parent;

    Node();
    Node(QVector<int>);
    ~Node();
};

class Tree {
    Node* root;
public:
    Tree();
    Tree(Node*);
    Node* getRoot();
    Tree& operator= (const Tree&);
    QVector<Node*> expansion(Node*);

};

#endif // TREE_H
