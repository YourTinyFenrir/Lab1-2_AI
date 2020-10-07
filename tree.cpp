#include "tree.h"
#include "QDebug"

Node::Node() { }

Node::Node(QVector<int> num) {

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            content.cell[i][j] = num[3*i + j];

    generation = 0;
    parent = nullptr;

}

Tree::Tree() {
    root = nullptr;
}

Tree::Tree(Node* nd) {
    root = nd;
}

void deleteNode(Node* nd) {

    qDebug() << "Delete node. Level " + QString::number(nd->generation);
    if (nd->children.size() > 0) {
        for (int i = 0; i < nd->children.size(); ++i)
            deleteNode(nd->children[i]);
    }

    delete nd; 
}

Tree::~Tree() {
    deleteNode(root);
}

Node* Tree::getRoot() {
    return root;
}

Tree& Tree::operator=(const Tree & tr) {

    this->root = new Node;
    this->root->parent = tr.root->parent;
    this->root->content = tr.root->content;
    this->root->children = tr.root->children;
    this->root->generation = tr.root->generation;

    return *this;

}

QVector<Node*> Tree::expansion(Node* p) {

    QVector<Field> ch = p->content.possibleFields();

    for (int i = 0; i < ch.size(); ++i) {
        Node* nd = new Node;
        nd->content = ch[i];
        nd->parent = p;
        nd->generation = p->generation + 1;
        p->children.push_back(nd);
    }

    return p->children;

}
