#include "tree.h"
#include "QDebug"

Node::Node() { }

Node::~Node() { }

Node::Node(QVector<int> num) {

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            state.cell[i][j] = num[3*i + j];

    generation = 0;
    parent = nullptr;

}

Tree::Tree() {
    root = nullptr;
}

Tree::Tree(Node* nd) {
    root = nd;
}

Node* Tree::getRoot() {
    return root;
}

Tree& Tree::operator=(const Tree & tr) {

    this->root = new Node;
    this->root->parent = tr.root->parent;
    this->root->state = tr.root->state;
    this->root->children = tr.root->children;
    this->root->generation = tr.root->generation;

    return *this;

}

QVector<Node*> Tree::expansion(Node* p) {

    QVector<Field> ch = p->state.possibleFields();

    for (int i = 0; i < ch.size(); ++i) {
        Node* nd = new Node;
        nd->state = ch[i];
        nd->parent = p;
        nd->generation = p->generation + 1;
        p->children.push_back(nd);
    }

    return p->children;

}
