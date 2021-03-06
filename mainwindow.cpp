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
    this->setWindowIcon(QIcon(":/res/img/title.png"));
    QPalette pal;
    QPixmap pixmap(":/res/img/background.jpg");
    pal.setBrush(QPalette::Window,QBrush(pixmap));
    setPalette(pal);
    setAutoFillBackground(true);
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
    mymain.show();
    this->showMinimized();
}
