#include "mymain.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QFontDatabase>
#include "mainwindow.h"

mymain::mymain(QWidget *parent) : QMainWindow(parent)
{

    int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    tetrisBox = new TetrisBox;
    nextTetrisBox = new NextTetrisBox;
    nextTetrisLabel = new QLabel(tr("<font color = white>NEXT：</font>"));
    controlLabel = new QLabel(tr("<font color = white>CONTROL：</font>"));
    w_controlLabel = new QLabel(tr("<font color = white>W-ROTATE</font>"));
    s_controlLabel = new QLabel(tr("<font color = white>S-DOWN</font>"));
    a_controlLabel = new QLabel(tr("<font color = white>A-UP</font>"));
    d_controlLabel = new QLabel(tr("<font color = white>D-RIGHT</font>"));
    enter_controlLabel = new QLabel(tr("<font color = white>ENTER-START</font>"));
    p_controlLabel = new QLabel(tr("<font color = white>P-PAUSE</font>"));
    r_controlLabel = new QLabel(tr("<font color = white>R-RESTART</font>"));
    esc_controlLabel = new QLabel(tr("<font color = white>ESC-END</font>"));
    spaceLabel = new QLabel(tr("<font color = white>Space-SKIP</font>"));
    scoreTitleLabel = new QLabel(tr("<font color = white>SCORE：</font>"));
    scoreLabel = new QLabel(tr("<font color = white>0</font>"));
    diffTitleLabel = new QLabel(tr("<font color = white>DIFFICULTY:</font>"));
    diffLabel = new QLabel(tr("<font color = white>0</font>"));
    QFont font("Microsoft YaHei", 15, 75);
    font.setFamily(fontFamilies.at(0));

    nextTetrisLabel->setFont(font);
    controlLabel->setFont(font);
    w_controlLabel->setFont(font);
    s_controlLabel->setFont(font);
    a_controlLabel->setFont(font);
    d_controlLabel->setFont(font);
    enter_controlLabel->setFont(font);
    p_controlLabel->setFont(font);
    r_controlLabel->setFont(font);
    esc_controlLabel->setFont(font);
    spaceLabel->setFont(font);
    scoreTitleLabel->setFont(font);
    scoreLabel->setFont(font);
    diffLabel->setFont(font);
    diffTitleLabel->setFont(font);



    mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(15);
    mainLayout->setVerticalSpacing(20);
    mainLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(nextTetrisLabel, 6, 3);
    mainLayout->addWidget(nextTetrisBox, 7, 3, 1, 2);
    mainLayout->addWidget(controlLabel, 0, 0, 1, 1);
    mainLayout->addWidget(w_controlLabel, 0, 1, 1, 1);
    mainLayout->addWidget(s_controlLabel, 1, 1, 1, 1);
    mainLayout->addWidget(a_controlLabel, 1, 0, 1, 1);
    mainLayout->addWidget(d_controlLabel, 1, 2, 1, 1);
    mainLayout->addWidget(r_controlLabel, 0, 2, 1, 1);
    mainLayout->addWidget(spaceLabel, 0, 3, 1, 1);
    mainLayout->addWidget(enter_controlLabel, 0, 4, 1, 1);
    mainLayout->addWidget(p_controlLabel, 1, 3, 1, 1);
    mainLayout->addWidget(esc_controlLabel, 1, 4, 1, 1);
    mainLayout->addWidget(tetrisBox, 3, 1, 14, 2);
    mainLayout->addWidget(scoreTitleLabel, 12, 3);
    mainLayout->addWidget(scoreLabel, 12, 4);
    mainLayout->addWidget(diffTitleLabel, 13,3);
    mainLayout->addWidget(diffLabel, 13, 4);

    QWidget *widget = new QWidget(this);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
    setWindowIcon(QIcon(":/res/img/title.png"));

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/res/img/game_bg.png")));
    setPalette(pal);

    QDesktopWidget *desktopWidget = QApplication::desktop();
    int w = (desktopWidget->width() - this->width()) / 2;
    int h = 5;
    move(w, h);

    nextStage = 100;
    speed = 100;

    status = STATUS_OFF;
    nextTetrisBox->updateNextTetris(tetris);
    setWindowTitle(tr("Tetromino - OFF"));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}

mymain::~mymain()
{

}

void mymain::setTimer(){
    timer->start(speed);
}



void mymain::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_D)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToRight())
            {
                tetrisBox->updateTetris(tetris);
            }
        }
    }
    else if (event->key() == Qt::Key_A)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToLeft())
            {
                tetrisBox->updateTetris(tetris);

            }
        }
    }

    else if (event->key() == Qt::Key_S)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToBottom())
            {
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
                updateScore();
            }
            else
            {
                QMediaPlayer *effect = new QMediaPlayer;
                effect->setMedia(QUrl::fromLocalFile("./res/sound/game_over.mp3"));
                effect->play();
                timer->stop();
                QString str;
                str +=  QString("Game Over1!\nYour Score is: %1!").arg(tetris.getScore());
                QMessageBox::information(this, tr("Game Over1"), str);
                status = STATUS_END;
                setWindowTitle(tr("Tetromino - END"));
            }
        }
    }
    else if (event->key() == Qt::Key_W)
    {
        if (tetris.rotate())
        {
            if (status == STATUS_ON)
            {
                tetrisBox->updateTetris(tetris);
            }
        }
    }

    else if (event->key() == Qt::Key_Space) {
        if(status == STATUS_ON)
        {
            if(tetris.moveToEnd())
            {
                tetrisBox->updateTetris(tetris);
            }
            else
            {
                QMediaPlayer *effect = new QMediaPlayer;
                effect->setMedia(QUrl::fromLocalFile("./res/sound/so_good.mp3"));
                effect->play();
                timer->stop();
                QString str;
                str +=  QString("Game Over2!\nYour Score is: %1!").arg(tetris.getScore());
                QMessageBox::information(this, tr("Game Over2"), str);
                status = STATUS_END;
                setWindowTitle(tr("Tetromino - END"));

            }
        }
    }

    else if (event->key() == Qt::Key_Enter||event->key() == Qt::Key_Return)
    {
        if (status == STATUS_PAUSE)
        {
            timer->start(speed);
            status = STATUS_ON;
            setWindowTitle(tr("Game_Tetris - ON"));
        }
        else if (status == STATUS_OFF)
        {
            tetris.createBlock();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            speed = 500;
            nextStage = 100;
            status = STATUS_ON;
            setWindowTitle(tr("Game_Tetris - ON"));
            timer->start(speed);
        }
        else if (status == STATUS_END)
        {
            tetris.clear();
            tetris.createBlock();
            speed = 500;
            nextStage = 100;
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            status = STATUS_ON;
            setWindowTitle(tr("Game_Tetris - ON"));
            timer->start(speed);
        }
    }
    else if (event->key() == Qt::Key_P)
    {
        if (status == STATUS_ON)
        {
            timer->stop();
            status = STATUS_PAUSE;
            setWindowTitle(tr("Tetromino - PAUSE"));

            box1->setWindowTitle("游戏暂停");
            box1->setText("按下H键继续游戏");
            box1->exec();
        }
    }

    else if (event->key() == Qt::Key_R)
    {
        if(status==STATUS_ON||status==STATUS_PAUSE)
        {
            timer->stop();
            QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确认要重新开始游戏吗，您的分数不会被记录",
                                                                     QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                                                                     QMessageBox::No);


            if(result==QMessageBox::No||result==QMessageBox::Cancel)
            {
                if(status==STATUS_ON)
                {
                    timer->start(speed);
                    return;
                }

            }
            else
            {
                tetris.clear();
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
                updateScore();
                status = STATUS_OFF;
                setWindowTitle(tr("Tetromino - OFF"));
            }
        }
        else
        {
            tetris.clear();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            status = STATUS_OFF;
            setWindowTitle(tr("Tetromino - OFF"));

        }

    }

    else if (event->key() == Qt::Key_Escape)
    {
        timer->stop();
        if(status==STATUS_ON||status==STATUS_PAUSE)
        {
            QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确认要关闭游戏吗?您的分数将不会被记录",
                                                                     QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                                                                     QMessageBox::No);
            if(result==QMessageBox::No||result==QMessageBox::Cancel)
            {
                if(status==STATUS_ON)
                {
                    timer->start(speed);
                    return;
                }
            }
            else
            {

                status = STATUS_OFF;
                QString str;
                int score = tetris.getScore();
                str += QString("%1").arg(score);
                QMessageBox *myclose=new QMessageBox();
                myclose->setWindowTitle("游戏结束");
                myclose->setText("您的分数为:"+str);

                tetris.clear();
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
                updateScore();
                setWindowTitle(tr("Tetromino - OFF"));
                myclose->exec();
            }

        }

        else
        {
            status = STATUS_OFF;
            QString str;
            int score = tetris.getScore();
            str += QString("%1").arg(score);
            QMessageBox *myclose=new QMessageBox();
            myclose->setWindowTitle("游戏结束");

            tetris.clear();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            setWindowTitle(tr("Tetromino - OFF"));
            myclose->exec();
        }
    }
}


void mymain::onTimer()
{
    if(tetris.moveToBottom())
    {
        tetrisBox->updateTetris(tetris);
        nextTetrisBox->updateNextTetris(tetris);
        updateScore();
    }
    else
    {
        timer->stop();
        QString str;
        str +=  QString("Game Over!\nYour Score is: %1!").arg(tetris.getScore());
        QMessageBox::information(this, tr("Game Over"), str);
        status = STATUS_END;
        setWindowTitle(tr("Tetromino - END"));
        QMediaPlayer *effect = new QMediaPlayer;
        effect->setMedia(QUrl::fromLocalFile("./res/sound/game_over.mp3"));
        effect->play();
    }
}


void mymain::updateScore()
{
    QString str,strDiff;
    int score = tetris.getScore();
    int diff = tetris.getDiff();
    str += QString("%1").arg(score);
    strDiff += QString("%1").arg(diff);
    scoreLabel->setText(str);
    if(score>=nextStage&&speed>=100){
        nextStage+=100;
        speed-=50;
        setTimer();
    }
    int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    scoreLabel->setText(str);
    diffLabel->setText(strDiff);
    QFont font("Microsoft YaHei", 15, 75);
    font.setFamily(fontFamilies.at(0));
    scoreLabel->setFont(font);
    scoreLabel->setStyleSheet("QLabel{color:white;}");
    diffLabel->setFont(font);
    diffLabel->setStyleSheet("QLabel{color:white;}");
}

void mymain::changeEvent(QEvent *event)
{
    if (event->type() != QEvent::WindowStateChange)
    {
        return;
    }
    if (windowState() == Qt::WindowMinimized)
    {
        if(status==STATUS_ON)
        {
            timer->stop();
            status=STATUS_PAUSE;
            setWindowTitle("Tetromino - PAUSE");
        }

    }
}

void mymain::closeEvent(QCloseEvent *event)
{
    if(status==STATUS_ON||status==STATUS_PAUSE)
    {
        timer->stop();
        QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确认要退出游戏吗，您的分数不会被记录",
                                                                 QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                                                                 QMessageBox::No);

        if (result==QMessageBox::Yes)
        {
            tetris.clear();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            status = STATUS_OFF;
            setWindowTitle(tr("Tetromino - OFF"));
            event->accept();
        }
        else
        {
            if(status==STATUS_ON)
            {
                timer->start();
            }
            event->ignore();
        }
    }
}
