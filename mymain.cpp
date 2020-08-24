#include "mymain.h"
#include <QMediaPlayer>

mymain::mymain(QWidget *parent) : QMainWindow(parent)
{

    tetrisBox = new TetrisBox;
    nextTetrisBox = new NextTetrisBox;
    nextTetrisLabel = new QLabel(tr("下一个："));
    controlLabel = new QLabel(tr("控制："));
    w_controlLabel = new QLabel(tr("W-旋转"));
    s_controlLabel = new QLabel(tr("S-向下移动"));
    a_controlLabel = new QLabel(tr("A-向左移动"));
    d_controlLabel = new QLabel(tr("D-向右移动"));
    h_controlLabel = new QLabel(tr("H-开始"));
    j_controlLabel = new QLabel(tr("J-暂停"));
    c_controlLabel = new QLabel(tr("C-重新开始"));
    m_controlLabel = new QLabel(tr("M-结束游戏"));
    spaceLabel = new QLabel(tr("Space-快速下落"));
    scoreTitleLabel = new QLabel(tr("得分："));
    scoreLabel = new QLabel(tr("0"));
    mainLayout = new QGridLayout;
    //设置mainLayout的水平和横向的间隔为20
    mainLayout->setHorizontalSpacing(20);
    mainLayout->setVerticalSpacing(20);
    //设置mainLayout居中
    mainLayout->setAlignment(Qt::AlignCenter);
    //添加各个widget
    mainLayout->addWidget(tetrisBox, 0, 0, 14, 1);
    mainLayout->addWidget(nextTetrisLabel, 0, 1);
    mainLayout->addWidget(nextTetrisBox, 1, 1, 1, 2);
    mainLayout->addWidget(controlLabel, 5, 1);
    mainLayout->addWidget(w_controlLabel, 6, 1);
    mainLayout->addWidget(s_controlLabel, 6, 2);
    mainLayout->addWidget(a_controlLabel, 7, 1);
    mainLayout->addWidget(d_controlLabel, 7, 2);
    mainLayout->addWidget(h_controlLabel, 8, 1);
    mainLayout->addWidget(j_controlLabel, 8, 2);
    mainLayout->addWidget(c_controlLabel, 9, 1);
    mainLayout->addWidget(m_controlLabel, 9, 2);
    mainLayout->addWidget(scoreTitleLabel, 12, 1);
    mainLayout->addWidget(scoreLabel, 12, 2);


    QWidget *widget = new QWidget(this);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);


    setPalette(Qt::gray);

    QDesktopWidget *desktopWidget = QApplication::desktop();
    int w = (desktopWidget->width() - this->width()) / 2;
    int h = 5;
    move(w, h);

    nextStage = 100;
    speed = 500;

    //初始化
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


//相应键盘事件
void mymain::keyPressEvent(QKeyEvent *event)
{
    //W键-进行旋转并更新游戏窗口内容
    if (event->key() == Qt::Key_W)
    {
        if (tetris.rotate())
        {
            //需要游戏状态为：正常进行
            if (status == STATUS_ON)
            {
                tetrisBox->updateTetris(tetris);
            }
        }
    }
    //A键-将方块向左移动并更新游戏窗口内容
    else if (event->key() == Qt::Key_A)
    {
        //需要游戏状态为：正常进行
        if (status == STATUS_ON)
        {
            if (tetris.moveToLeft())
            {
                tetrisBox->updateTetris(tetris);

            }
        }
    }
    //S键-将方块向下移动并更新游戏窗口内容
    else if (event->key() == Qt::Key_S)
    {
        //需要游戏状态：正常进行
        if (status == STATUS_ON)
        {
            if (tetris.moveToBottom())
            {
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
                updateScore();
            }
            else    //游戏结束
            {
                QMediaPlayer *effect = new QMediaPlayer;
                effect->setMedia(QUrl::fromLocalFile("C:\\Users\\10852\\Desktop\\WorkSpace\\Qt\\Tetromino\\game_over.mp3"));
                effect->play();
                //计时器停止
                timer->stop();
                //输出结束提示
                QString str;
                str +=  QString("Game Over1!\nYour Score is: %1!").arg(tetris.getScore());
                QMessageBox::information(this, tr("Game Over1"), str);
                //更改游戏状态为：游戏结束
                status = STATUS_END;
                setWindowTitle(tr("Tetromino - END"));
            }
        }
    }
    //空格下落
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
                effect->setMedia(QUrl::fromLocalFile("C:\\Users\\10852\\Desktop\\WorkSpace\\Qt\\Tetromino\\game_over.mp3"));
                effect->play();
                //计时器停止
                timer->stop();
                //输出结束提示
                QString str;
                str +=  QString("Game Over2!\nYour Score is: %1!").arg(tetris.getScore());
                QMessageBox::information(this, tr("Game Over2"), str);
                //更改游戏状态为：游戏结束
                status = STATUS_END;
                setWindowTitle(tr("Tetromino - END"));

            }
        }
    }
    //D键-将方块向右移动并更新游戏窗口内容
    else if (event->key() == Qt::Key_D)
    {
        //需要游戏状态为：正常进行
        if (status == STATUS_ON)
        {
            if (tetris.moveToRight())
            {
                tetrisBox->updateTetris(tetris);
            }
        }
    }
    //H键-开始游戏
    //不同状态的相应：
    //之前状态    之后状态
    //游戏暂停 -> 正常进行
    //还未开始 -> 正常进行
    //游戏结束 -> 正常进行
    else if (event->key() == Qt::Key_H)
    {
        if (status == STATUS_PAUSE)
        {
            timer->start(speed);
            status = STATUS_ON;
            setWindowTitle(tr("Game_Tetris - ON"));
        }
        else if (status == STATUS_OFF)
        {
            //初始化窗口视图
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
            //初始化tetris
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
    //J键-游戏暂停
    else if (event->key() == Qt::Key_J)
    {
        //需要游戏状态为：正常进行
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
    //C键-重新开始游戏
    else if (event->key() == Qt::Key_C)
    {
        QMessageBox *box=new QMessageBox();
        box->setText("确定要重新开始吗？您的分数将会清零");
        timer->stop();
        box->setStandardButtons(QMessageBox::No|QMessageBox::Yes);
        if(box->exec()==QMessageBox::No)
        {
            if(status==STATUS_ON)
            {
                timer->start(500);
            }
            return;
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
    //M键-关闭游戏
    else if (event->key() == Qt::Key_M)
    {
        QMessageBox *box=new QMessageBox();
        box->setText("确定要关闭游戏吗？您的分数将不会被记录");
        timer->stop();
        box->setStandardButtons(QMessageBox::No|QMessageBox::Yes);
        if(box->exec()==QMessageBox::No)
        {
            if(status==STATUS_ON)
            {
                timer->start(500);
            }
            return;
        }
        else
        {
            QString str;
            int score = tetris.getScore();
            str += QString("%1").arg(score);
            QMessageBox *myclose=new QMessageBox();
            myclose->setWindowTitle("游戏结束");
            myclose->setText("您的分数为:"+str);
            myclose->exec();
            close();
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
        effect->setMedia(QUrl::fromLocalFile("C:\\Users\\10852\\Desktop\\WorkSpace\\Qt\\Tetromino\\game_over.mp3"));
        effect->play();
    }
}


void mymain::updateScore()
{
    QString str;
    int score = tetris.getScore();
    str += QString("%1").arg(score);
    scoreLabel->setText(str);
    if(score>=nextStage&&speed>=100){
        nextStage+=100;
        speed-=50;
        setTimer();
    }
    scoreLabel->setText(str);
}


//若窗口最小化就停止计时器
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
