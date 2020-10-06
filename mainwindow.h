#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data.h"
#include "QVector"
#include "field.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showOnScreen(Node*, int);
    void showResults();
    void setDefaultData();
private slots:


    void on_b1up_clicked();
    void on_b1down_clicked();
    void on_b2up_clicked();
    void on_b2down_clicked();
    void on_b3up_clicked();
    void on_b3down_clicked();

    void on_bStep_clicked();

    void on_bCycle_clicked();

    void on_bDrop_clicked();

private:
    Ui::MainWindow *ui;

    Data data;
    QVector<Node*> outputList1;
    QVector<Node*> outputList2;
    QVector<Node*> outputList3;
    QString outputInfo;
    int num1;
    int num2;
    int num3;
};
#endif // MAINWINDOW_H
