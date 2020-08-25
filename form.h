#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QGridLayout>
#include<qgridlayout.h>
#include <QFile>
#include <QMessageBox>
#include <QObject>
#include <QTextStream>
#include <QtDebug>
#include <QIcon>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

    void myshow();
private slots:


private:
    Ui::Form *ui;
};

#endif // FORM_H
