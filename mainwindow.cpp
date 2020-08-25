#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quitdialog.h"
#include "ui_quitdialog.h"
#include <QDialog>
#include "form.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("俄罗斯方块");
    this->setWindowIcon(QIcon("./images/title.png"));
    this->setStyleSheet("border-image:url(./images/background.jpg);background-repeat:no-repeat;");
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    quit.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    myform.show();
}


void MainWindow::on_pushButton_clicked()
{
    mymian.show();
    this->showMinimized();
}
