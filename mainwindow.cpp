#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setDefaultData();
    ui->textEdit->setReadOnly(true);

    ui->comboBox->addItem("Слепой поиск в ширину");
    ui->comboBox->addItem("Слепой поиск в глубину");
    ui->comboBox->addItem("Жадный поиск + Кол-во фишек не на своих местах");
    ui->comboBox->addItem("Жадный поиск + Манхэттенское расстояние");
    ui->comboBox->addItem("А* + Кол-во фишек не на своих местах");
    ui->comboBox->addItem("А* + Манхэттенское расстояние");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showOnScreen(Node* nd, int num) {

    switch(num) {
    case 0:
        ui->s10->setNum(nd->content.cell[0][0]);
        ui->s11->setNum(nd->content.cell[0][1]);
        ui->s12->setNum(nd->content.cell[0][2]);
        ui->s13->setNum(nd->content.cell[1][0]);
        ui->s14->setNum(nd->content.cell[1][1]);
        ui->s15->setNum(nd->content.cell[1][2]);
        ui->s16->setNum(nd->content.cell[2][0]);
        ui->s17->setNum(nd->content.cell[2][1]);
        ui->s18->setNum(nd->content.cell[2][2]);
        break;
    case 1:
        ui->s20->setNum(nd->content.cell[0][0]);
        ui->s21->setNum(nd->content.cell[0][1]);
        ui->s22->setNum(nd->content.cell[0][2]);
        ui->s23->setNum(nd->content.cell[1][0]);
        ui->s24->setNum(nd->content.cell[1][1]);
        ui->s25->setNum(nd->content.cell[1][2]);
        ui->s26->setNum(nd->content.cell[2][0]);
        ui->s27->setNum(nd->content.cell[2][1]);
        ui->s28->setNum(nd->content.cell[2][2]);
        break;
    case 2:
        ui->s30->setNum(nd->content.cell[0][0]);
        ui->s31->setNum(nd->content.cell[0][1]);
        ui->s32->setNum(nd->content.cell[0][2]);
        ui->s33->setNum(nd->content.cell[1][0]);
        ui->s34->setNum(nd->content.cell[1][1]);
        ui->s35->setNum(nd->content.cell[1][2]);
        ui->s36->setNum(nd->content.cell[2][0]);
        ui->s37->setNum(nd->content.cell[2][1]);
        ui->s38->setNum(nd->content.cell[2][2]);
        break;
    }


}

void MainWindow::showResults() {

    num1 = 0; num2 = 0; num3 = 0;

    ui->bStep->hide();
    ui->bCycle->hide();
    ui->b1up->show();
    ui->b1down->show();
    ui->b2up->hide();
    ui->b2down->hide();
    ui->b3up->hide();
    ui->b3down->hide();
    ui->bDrop->show();
    ui->comboBox->setVisible(true);

    outputList1 = data.getFinalResult();
    showOnScreen(outputList1[0], 0);
    outputInfo += data.getInfoStr();
    ui->textEdit->setText(outputInfo);

}

void MainWindow::setDefaultData() {

    num1 = 0; num2 = 0; num3 = 0;
    outputList1.clear();
    outputList2.clear();
    outputList3.clear();
    outputInfo.clear();
    ui->textEdit->clear();
    ui->bStep->show();
    ui->bCycle->show();
    ui->bDrop->hide();
    ui->b1up->hide();
    ui->b1down->hide();
    ui->b2up->hide();
    ui->b2down->hide();
    ui->b3up->hide();
    ui->b3down->hide();

    QVector<int> vec;
    vec.push_back(5); vec.push_back(8); vec.push_back(3); vec.push_back(4); vec.push_back(0);
    vec.push_back(2); vec.push_back(7); vec.push_back(6); vec.push_back(1);

    Node nd(vec);
    data.refresh(&nd);
    showOnScreen(&nd, 0);

    QVector<int> vec1(9);
    Node nd1(vec1);
    showOnScreen(&nd1, 1);
    showOnScreen(&nd1, 2);

    vec.clear();
    vec.push_back(1); vec.push_back(2); vec.push_back(3); vec.push_back(4); vec.push_back(5);
    vec.push_back(6); vec.push_back(7); vec.push_back(8); vec.push_back(0);

    Field f1(vec);
    data.setFS(f1);

}

void MainWindow::on_bStep_clicked() {

    ui->comboBox->setVisible(false);
    ui->bCycle->show();
    ui->bDrop->hide();
    ui->b1up->show();
    ui->b2up->show();
    ui->b3up->show();

    bool isFinished;
    switch (ui->comboBox->currentIndex()) {
    case 0:
        isFinished = data.stepSearch("BFS");
        break;
    case 1:
        isFinished = data.stepSearch("DFS");
        break;
    case 2:
        isFinished = data.stepSearch("GS1");
        break;
    case 3:
        isFinished = data.stepSearch("GS2");
        break;
    case 4:
        isFinished = data.stepSearch("A*1");
        break;
    case 5:
        isFinished = data.stepSearch("A*2");
        break;
    }

    outputList1 = data.getChildrenForExpansion();
    outputList2 = data.getNewChildren();
    outputList3 = data.getRepeatingChildren();\

    QVector<int> temp(9);
    Node nd(temp);

    if (isFinished)
        showResults();
    else  {
        if (outputList1.size() > 0)
            showOnScreen(outputList1[0], 0);
        else
            showOnScreen(&nd, 1);
        if (outputList1.size() <= 1) {
            ui->b1up->hide();
            ui->b1down->hide();
        }

        if (outputList2.size() > 0)
            showOnScreen(outputList2[0], 1);
        else
            showOnScreen(&nd, 2);
        if (outputList2.size() <= 1) {
            ui->b2up->hide();
            ui->b2down->hide();
        }

        if (outputList3.size() > 0)
            showOnScreen(outputList3[0], 2);
        else
            showOnScreen(&nd, 3);
        if (outputList3.size() <= 1) {
            ui->b3up->hide();
            ui->b3down->hide();
        }

        num1 = 0; num2 = 0; num3 = 0;
        outputInfo += data.getInfoStr();
        ui->textEdit->setText(outputInfo);
    }

}

void MainWindow::on_bCycle_clicked() {

    ui->comboBox->setVisible(false);
    ui->bStep->show();
    ui->bDrop->hide();
    bool isFinished;

    switch(ui->comboBox->currentIndex()) {
    case 0:
        isFinished = false;
        while (!isFinished)
            isFinished = data.stepSearch("BFS");
        break;
    case 1:
        isFinished = false;
        while (!isFinished)
            isFinished = data.stepSearch("DFS");
        break;
    case 2:
        isFinished = false;
        while (!isFinished)
            isFinished = data.stepSearch("GS1");
        break;
    case 3:
        isFinished = false;
        while (!isFinished)
            isFinished = data.stepSearch("GS2");
        break;
    case 4:
        isFinished = false;
        while (!isFinished)
            isFinished = data.stepSearch("A*1");
        break;
    case 5:
        isFinished = false;
        while (!isFinished)
            isFinished = data.stepSearch("A*2");
        break;
    }
    showResults();

}

void MainWindow::on_bDrop_clicked() {
    setDefaultData();
}

void MainWindow::on_b1up_clicked() {

    num1++;
    ui->b1down->show();
    if (num1 + 1 == outputList1.size())
        ui->b1up->hide();
    showOnScreen(outputList1[num1], 0);

}

void MainWindow::on_b1down_clicked() {

    num1--;
    ui->b1up->show();
    if (num1 == 0)
        ui->b1down->hide();
    showOnScreen(outputList1[num1], 0);

}

void MainWindow::on_b2up_clicked() {

    num2++;
    ui->b2down->show();
    if (num2 + 1 == outputList2.size())
        ui->b2up->hide();
    showOnScreen(outputList2[num2], 1);

}

void MainWindow::on_b2down_clicked() {

    num2--;
    ui->b2up->show();
    if (num2 == 0)
        ui->b2down->hide();
    showOnScreen(outputList2[num2], 1);

}

void MainWindow::on_b3up_clicked() {

    num3++;
    ui->b3down->show();
    if (num3 + 1 == outputList3.size())
        ui->b3up->hide();
    showOnScreen(outputList3[num3], 2);

}

void MainWindow::on_b3down_clicked() {

    num3--;
    ui->b3up->show();
    if (num3 == 0)
        ui->b3down->hide();
    showOnScreen(outputList3[num3], 2);

}
