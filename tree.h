#ifndef TREE_H
#define TREE_H

#include "field.h"

struct Node {
    Field content;
    QVector<Node*> children;
    Node* parent;

    Node();
};

class Tree {
    Node* root;
public:
    Tree();
    Tree(Field);
    ~Tree();
    Node* getRoot();
    Tree& operator= (const Tree&);
    QVector<Node*> addChildren(Node*);
};

#endif // TREE_H
