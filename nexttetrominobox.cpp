#include "nexttetrominobox.h"

NextTetrisBox::NextTetrisBox(QWidget *parent) : QWidget(parent)
{

    //初始化nextBlock
    for (int i = 0; i < COUNT; i++)
    {
        nextBlock.x[i] = -1;
        nextBlock.y[i] = -1;
    }
    nextBlock.centerX = -1;
    nextBlock.centerY = -1;
    nextBlock.ID = 0;
    nextBlock.color = 10;
    //设置本“下一个”窗口的宽度和高度
    //并设置背景为黑色
    int w = CTetromino::getNextWidth();
    int h = CTetromino::getNextHeight();
    setFixedSize(w, h);
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/res/img/next_bg.png")));
    setPalette(pal);
    setAutoFillBackground(true);
}


void NextTetrisBox::updateNextTetris(CTetromino tetris)
{
    nextBlock = tetris.getNextBlock();
    for (int i = 0; i < COUNT; i++)
    {
        nextBlock.x[i] -= RESTX;
        nextBlock.y[i] += RESTY;
    }
    //重新绘制
    repaint();
}


void NextTetrisBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    painter.translate(0, 0);
    switch (nextBlock.color) {
    case 0:
        pix.load(":/res/img/block_red.png");
        break;
    case 1:
        pix.load(":/res/img/block_orange.png");
        break;
    case 2:
        pix.load(":/res/img/block_yellow.png");
        break;
    case 3:
        pix.load(":/res/img/block_green.png");
        break;
    case 4:
        pix.load(":/res/img/block_blue.png");
        break;
    case 5:
        pix.load(":/res/img/block_pink.png");
        break;
    case 6:
        pix.load(":/res/img/block_purple.png");
        break;
    default:
        pix.load(":/res/img/block_pink.png");
        break;

    }

    //绘制nextBlock中的内容
    for (int i = 0; i < COUNT; i++)
    {
        int x = nextBlock.x[i];
        int y = nextBlock.y[i];
        int x1 = x * WIDTH + x * INTERVAL;
        int y1 = y * HEIGHT + y * INTERVAL;
        painter.drawPixmap(x1, y1, WIDTH, HEIGHT,pix);
    }
}
