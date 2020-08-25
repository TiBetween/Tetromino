#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->setWindowTitle("排行榜");
    this->setWindowIcon(QIcon(":/res/img/title.png"));

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/res/img/background.jpg")));
    setPalette(pal);

    QStringList list;
    QFile file("rank.txt");

    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        return;
    }
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        list+=line;
    }
   file.close();

   QPalette pe1;
   pe1.setColor(QPalette::WindowText,Qt::red);

   QLabel *label1=new QLabel(this);
   label1->setGeometry(120,80,300,30);
   label1->setText(list[0]);
   label1->setPalette(pe1);
   label1->show();


   QLabel *label2=new QLabel(this);
   label2->setGeometry(120,120,300,30);
   label2->setText(list[1]);
   label2->setPalette(pe1);
   label2->show();

   QLabel *label3=new QLabel(this);
   label3->setGeometry(120,160,300,30);
   label3->setText(list[2]);
   label3->setPalette(pe1);
   label3->show();

   QLabel *label4=new QLabel(this);
   label4->setGeometry(120,200,300,30);
   label4->setText(list[3]);
   label4->setPalette(pe1);
   label4->show();

   QLabel *label5=new QLabel(this);
   label5->setGeometry(120,240,300,30);
   label5->setText(list[4]);
   label5->setPalette(pe1);
   label5->show();
}

Form::~Form()
{
    delete ui;

}

