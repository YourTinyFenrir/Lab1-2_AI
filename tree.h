#ifndef TREE_H
#define TREE_H

#include "field.h"

struct Node {
    Field content;
    QVector<Node*> children;
    Node* parent;

    Node();
    Node(QVector<int>);
};

class Tree {
    Node* root;
public:
    Tree();
    Tree(Node*);
    ~Tree();
    Node* getRoot();
    Tree& operator= (const Tree&);
    QVector<Node*> expansion(Node*);

};

#endif // TREE_H
