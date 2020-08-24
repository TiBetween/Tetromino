#include "quitdialog.h"
#include "ui_quitdialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("退出");
}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_buttonBox_accepted()
{
    QApplication *app;
    app->quit();
}
