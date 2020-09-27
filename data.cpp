#include "data.h"

Data::Data() {
    numOfNodes = 0;
    numOfSteps = 0;
}

void Data::setTree(Field f) {
    Tree tr(f);
    tree = tr;
}

void Data::setFS(Field f) {
    finalState = f;
}

Field Data::getContent(int num) {
    return content[num];
}

int Data::getContentSize() {
    return contentSize;
}

bool Data::isComplete(Node* nd) {

    bool res = true;

    for (int i = 0; i < 3 && res; ++i)
        for (int j = 0; j < 3 && res; ++j)
            if (finalState.cell[i][j] != nd->content.cell[i][j])
                res = false;

    return res;

}

void Data::setResultToContent() {

    QVector<Field> res;

    bool isFinded = false;
    for (int i = 0; !isFinded; ++i)
        if (isComplete(theOldestChildren[i])) {
            isFinded = true;
            Node* curNode = theOldestChildren[i];
            while (curNode != nullptr) {
                res.push_front(curNode->content);
                curNode = curNode->parent;
            }
        }

    content = res;

}

bool Data::stepBS() {

    QVector<Node*> temp;
    bool res = false;

    if (theOldestChildren.size() == 0) {
        temp = tree.addChildren(tree.getRoot());
        theOldestChildren.append(temp);
        for (int i = 0; i < theOldestChildren.size(); ++i)
            if (isComplete(theOldestChildren[i]))
                res = true;

    }
    else
        for (int i = 0; i < theOldestChildren.size(); ++i)
            temp = tree.addChildren(theOldestChildren[i]);

    theOldestChildren.clear();
    theOldestChildren.append(temp);

    for (int i = 0; i < theOldestChildren.size(); ++i) {
        content.push_back(theOldestChildren[i]->content);
        if (isComplete(theOldestChildren[i]))
            res = true;
    }

    contentSize = theOldestChildren.size();
    numOfSteps++;

    return res;

}

void Data::blindSearch() {

    bool isFinished = false;

    while (!isFinished) {
        isFinished = stepBS();
    }

}
