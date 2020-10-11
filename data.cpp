#include "data.h"

Data::Data() {}

void Data::refresh(Node* nd) {
    childrenForExpansion.clear();
    newChildren.clear();
    repeatingChildren.clear();
    addedChildren.clear();
    numOfSteps = 0;

    Tree tr(nd);
    tree = tr;
    childrenForExpansion.push_back(tree.getRoot());
    addedChildren.insert(getKey(tree.getRoot()), tree.getRoot());
}

QVector<Node*> Data::getChildrenForExpansion() {
    return childrenForExpansion;
}

QVector<Node*> Data::getNewChildren() {
    return newChildren;
}

QVector<Node*> Data::getRepeatingChildren() {
    return repeatingChildren;
}

QString Data::getInfoStr() {
   return infoStr;
}

void Data::setFS(Field f) {
    finalState = f;
}

int Data::getKey(Node* nd) {
    return nd->content.toInt();
}

bool Data::goalTest(Node* nd) {

    bool res = true;

    for (int i = 0; i < 3 && res; ++i)
        for (int j = 0; j < 3 && res; ++j)
            if (finalState.cell[i][j] != nd->content.cell[i][j])
                res = false;

    return res;

}

QVector<Node*> Data::getFinalResult() {

    QVector<Node*> res;
    Node* curNode;

    bool isFinished = false;
    for (int i = 0; i < newChildren.size()  && !isFinished; ++i)
        if (goalTest(newChildren[i])) {
            isFinished = true;
            curNode = newChildren[i];
        }

    while (curNode != nullptr) {
        res.push_front(curNode);
        curNode = curNode->parent;
    }

    return res;

}

bool Data::stepSearch(QString option) {

    bool res = false;
    QVector<Node*> temp;
    QString depthResStr;
    repeatingChildren.clear();

    newChildren = tree.expansion(childrenForExpansion[0]);
    for (int i = 0; i < newChildren.size(); ++i) {
        if (addedChildren.find(getKey(newChildren[i])) == addedChildren.end()) {
            if (goalTest(newChildren[i])) {
                res = true;
                depthResStr = QString::number(newChildren[i]->generation);
            }
            temp.push_back(newChildren[i]);
        }
        else
            repeatingChildren.push_back(newChildren[i]);
    }

    childrenForExpansion.removeFirst();

    if (option == "BFS") {
        childrenForExpansion.append(temp);
        for (int i = 0; i < temp.size(); ++i)
            addedChildren.insert(getKey(temp[i]), temp[i]);
    }

    if (option == "DFS") {
        for (int i = 0; i < temp.size(); ++i) {
            childrenForExpansion.push_front(temp[temp.size()-1-i]); // добавление в начало вектора
            addedChildren.insert(getKey(temp[i]), temp[i]);
        }
    }

    if (option == "GS1") {
        childrenForExpansion.append(temp);
        for (int i = 0; i < temp.size(); ++i)
            addedChildren.insert(getKey(temp[i]), temp[i]);

        int min = 100; int min_i = 0; // Поиск состояния с наибольшим числом значений не на "своих" местах
        for (int i = 0; i < childrenForExpansion.size(); ++i) {
            int numCells = childrenForExpansion[i]->content.cellsOnIncorrectPosition(finalState);
            if (numCells < min) {
                min = numCells;
                min_i = i;
            }
        }
        Node* temp = childrenForExpansion[min_i]; // Добавление узла, который будет раскрыт на следующем шаге, в начало вектора
        childrenForExpansion.remove(min_i);
        childrenForExpansion.push_front(temp);
    }

    if (option == "GS2") {
        childrenForExpansion.append(temp);
        for (int i = 0; i < temp.size(); ++i)
            addedChildren.insert(getKey(temp[i]), temp[i]);

        int min = 100; int min_i = 0; // Поиск состояния с наименьшим Манхэттенским расстоянием
        for (int i = 0; i < childrenForExpansion.size(); ++i) {
            int dist = childrenForExpansion[i]->content.manhattanDistance(finalState);
            if (dist < min) {
                min = dist;
                min_i = i;
            }
        }
        Node* temp = childrenForExpansion[min_i]; // Добавление узла, который будет раскрыт на следующем шаге, в начало вектора
        childrenForExpansion.remove(min_i);
        childrenForExpansion.push_front(temp);
    }

    if (option == "A*1") {
        childrenForExpansion.append(temp);
        for (int i = 0; i < temp.size(); ++i)
            addedChildren.insert(getKey(temp[i]), temp[i]);

        int min = 1000000000; int min_i = 0; // Поиск состояния с наибольшим числом значений не на "своих" местах (также учитываем глубину узла)
        for (int i = 0; i < childrenForExpansion.size(); ++i) {
            int numCells = childrenForExpansion[i]->content.cellsOnIncorrectPosition(finalState);
            int depth = childrenForExpansion[i]->generation;
            if (numCells + depth < min) {
                min = numCells + depth;
                min_i = i;
            }
        }
        Node* temp = childrenForExpansion[min_i]; // Добавление узла, который будет раскрыт на следующем шаге, в начало вектора
        childrenForExpansion.remove(min_i);
        childrenForExpansion.push_front(temp);
    }

    if (option == "A*2") {
        childrenForExpansion.append(temp);
        for (int i = 0; i < temp.size(); ++i)
            addedChildren.insert(getKey(temp[i]), temp[i]);

        int min = 1000000000; int min_i = 0; // Поиск состояния с наименьшим Манхэттенским расстоянием (также учитываем глубину узла)
        for (int i = 0; i < childrenForExpansion.size(); ++i) {
            int numCells = childrenForExpansion[i]->content.manhattanDistance(finalState);
            int depth = childrenForExpansion[i]->generation;
            if (numCells + depth < min) {
                min = numCells + depth;
                min_i = i;
            }
        }
        Node* temp = childrenForExpansion[min_i]; // Добавление узла, который будет раскрыт на следующем шаге, в начало вектора
        childrenForExpansion.remove(min_i);
        childrenForExpansion.push_front(temp);
    }

    numOfSteps++;

    if (!res)
        infoStr = "Решение не найдено. Заполнено узлов: " + QString::number(addedChildren.size()) +
                ". Выполнено шагов: " + QString::number(numOfSteps) + "\n";
    else
        infoStr = "Решение найдено. Заполнено узлов: " + QString::number(addedChildren.size()) +
                ". Выполнено шагов: " + QString::number(numOfSteps) + ". Количество шагов для решения: " + depthResStr + "\n";

    return res;

}
