#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "quitdialog.h"
#include "form.h"
#include "mymain.h"

#define STATUS_ON 0     //游戏正常进行
#define STATUS_PAUSE 1  //游戏暂停
#define STATUS_OFF 2    //游戏未开始
#define STATUS_END 3    //游戏结束

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class Form;
class Dialog;
class mymain;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:


    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Form myform;
    Dialog quit;
    mymain mymain;
};
#endif // MAINWINDOW_H
