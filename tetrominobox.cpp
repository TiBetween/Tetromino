#include "tetrominobox.h"

TetrisBox::TetrisBox(QWidget *parent) : QWidget(parent)
{
    //对block初始化
    for (int i = 0; i < COUNT; i++)
    {
        block.x[i] = -1;
        block.y[i] = -1;
    }
    block.centerX = -1;
    block.centerY = -1;
    block.ID = -1;
    //对box初始化
    for (int i = 0; i < MAXX; i++)
    {
        for (int j = 0; j < MAXY; j++)
        {
            box[i][j] = 0;
        }
    }

    //设置本游戏窗口的宽度和高度
    //并设置背景为黑色
    int w = CTetromino::getWidth();
    int h = CTetromino::getHeight();
    setFixedSize(w, h);
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/res/img/main_bg.png")));
    setPalette(pal);
    setAutoFillBackground(true);
}


void TetrisBox::updateTetris(CTetromino tetris)
{
    //更新block
    block = tetris.getBlock();
    //更新box
    for (int i = 0; i < MAXX; i++)
    {
        for (int j = 0; j < MAXY; j++)
        {
            box[i][j] = tetris.getBox(i, j);
        }
    }
    repaint();
}


void TetrisBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    QPen pen;
//    QBrush brush;
//    pen.setStyle(Qt::SolidLine);
//    pen.setColor(QColor(255, 255, 255));
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(QColor(255, 255, 255));
//    painter.setPen(pen);
//    painter.setBrush(brush);

    QPixmap pix;
    painter.translate(0, 0);
    switch(block.color)
    {
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
    //绘制box中的内容
    for (int i = 0; i < MAXX; i++)
    {
        for (int j = 0; j < MAXY; j++)
        {
            if (box[i][j] == 1)
            {
                int x = i * WIDTH + i * INTERVAL;
                int y = j * HEIGHT + j * INTERVAL;

                painter.drawPixmap(x + 7, y + 8, WIDTH, HEIGHT, pix);
            }
        }
    }
    //绘制block中的内容
    for (int i = 0; i < COUNT; i++)
    {
        int x = block.x[i];
        int y = block.y[i];
        int x1 = x * WIDTH + x * INTERVAL;
        int y1 = y * HEIGHT + y * INTERVAL;
        painter.drawPixmap(x1 + 7, y1 + 8, WIDTH, HEIGHT, pix);
    }
}
