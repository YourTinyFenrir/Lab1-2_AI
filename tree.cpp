#include "tree.h"

Node::Node() { }

Tree::Tree() { }

Tree::Tree(Field f) {

    root = new Node;
    root->content = f;
    root->parent = nullptr;

}

void deleteNode(Node* nd) {

    if (nd->children.size() > 0)
        for (int i = 0; i < nd->children.size(); ++i)
            deleteNode(nd->children[i]);
    else
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

    return *this;

}

QVector<Node*> Tree::addChildren(Node* p) {

    QVector<Field> ch = p->content.possibleFields();

    for (int i = 0; i < ch.size(); ++i) {
        Node* nd = new Node;
        nd->content = ch[i];
        nd->parent = p;
        p->children.push_back(nd);
    }

    return p->children;

}
