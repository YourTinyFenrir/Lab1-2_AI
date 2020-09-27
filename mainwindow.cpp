#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setDefaultData();

    ui->comboBox->addItem("Слепой поиск");
    ui->comboBox->addItem("2 вариант");
    ui->comboBox->addItem("3 вариант");
    ui->comboBox->addItem("4 вариант");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fieldToScreen(Field f) {

    ui->label_0->setNum(f.cell[0][0]);
    ui->label_1->setNum(f.cell[0][1]);
    ui->label_2->setNum(f.cell[0][2]);
    ui->label_3->setNum(f.cell[1][0]);
    ui->label_4->setNum(f.cell[1][1]);
    ui->label_5->setNum(f.cell[1][2]);
    ui->label_6->setNum(f.cell[2][0]);
    ui->label_7->setNum(f.cell[2][1]);
    ui->label_8->setNum(f.cell[2][2]);

}

void MainWindow::showResults() {

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_5->show();
    ui->comboBox->setVisible(true);

    data.setResultToContent();
    contentNum = 0;
    fieldToScreen(data.getContent(contentNum));
    // Вывод доп данных сбоку

}

void MainWindow::setDefaultData() {

    contentNum = 0;
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();

    QVector<int> vec;
    vec.push_back(1); vec.push_back(2); vec.push_back(3); vec.push_back(4); vec.push_back(0);
    vec.push_back(6); vec.push_back(7); vec.push_back(5); vec.push_back(8);

    Field f(vec);
    data.setTree(f);
    fieldToScreen(f);

    vec.clear();
    vec.push_back(1); vec.push_back(2); vec.push_back(3); vec.push_back(4); vec.push_back(5);
    vec.push_back(6); vec.push_back(7); vec.push_back(8); vec.push_back(0);

    Field f1(vec);
    data.setFS(f1);

}

void MainWindow::on_pushButton_clicked() {

    ui->comboBox->setVisible(false);
    ui->pushButton_3->show();
    ui->pushButton_4->hide();

    bool isFinished = data.stepBS();
    if (isFinished)
        showResults();
    else {
        contentNum = 0;
        fieldToScreen(data.getContent(contentNum));
    }

}

void MainWindow::on_pushButton_2_clicked() {

    ui->comboBox->setVisible(false);
    ui->pushButton_3->show();
    ui->pushButton_4->hide();

    switch(ui->comboBox->currentIndex()) {
        case 0:
        data.blindSearch();
        showResults();
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }

}

void MainWindow::on_pushButton_3_clicked() {

    contentNum++;
    ui->pushButton_4->show();
    if (contentNum + 1 == data.getContentSize())
        ui->pushButton_3->hide();
    fieldToScreen(data.getContent(contentNum));

}

void MainWindow::on_pushButton_4_clicked() {

    contentNum--;
    ui->pushButton_3->show();
    if (contentNum == 0)
        ui->pushButton_4->hide();
    fieldToScreen(data.getContent(contentNum));

}

void MainWindow::on_pushButton_5_clicked() {
    setDefaultData();
}
