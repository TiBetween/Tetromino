#ifndef MYMAIN_H
#define MYMAIN_H

#include <QMainWindow>
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QKeyEvent>
#include <QTimer>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>
#include <QFontDatabase>

#include "ctetromino.h"
#include "tetrominobox.h"
#include "nexttetrominobox.h"

#define STATUS_ON 0     //游戏正常进行
#define STATUS_PAUSE 1  //游戏暂停
#define STATUS_OFF 2    //游戏未开始
#define STATUS_END 3    //游戏结束

class mymain : public QMainWindow
{
    Q_OBJECT
public:
    void record();
    explicit mymain(QWidget *parent = nullptr);
    ~mymain();
    void keyPressEvent(QKeyEvent *event);   //响应键盘事件
    void keyReleaseEvent(QKeyEvent *e);
    void changeEvent(QEvent *event);        //窗口最小化后暂停
    void closeEvent(QCloseEvent *event);
    void updateScore();                     //更新分数的数据和显示
    void setTimer();                        //设置计时器，方便加速
public slots:
    void onTimer();
public slots:
    void onrepeatTimer();
private:
    int speed;
    int nextStage;
    Qt::Key key;
    Qt::Key keytemp;
    QMessageBox *box1=new QMessageBox();
    int status;                     //游戏状态
    CTetromino tetris;                  //俄罗斯方块类对象
    QTimer *timer;                  //计时器
    QTimer *repeatTimer;
    TetrisBox *tetrisBox;           //游戏窗口
    NextTetrisBox *nextTetrisBox;   //“下一个”窗口
    QGridLayout *mainLayout;        //mainLayout
    QLabel *nextTetrisLabel;        //“下一个”窗口的标签
    QLabel *controlLabel;           //“控制”标签
    QLabel *w_controlLabel;         //W键的标签
    QLabel *s_controlLabel;         //S键的标签
    QLabel *a_controlLabel;         //A键的标签
    QLabel *d_controlLabel;         //D键的标签
    QLabel *enter_controlLabel;         //Enter键的标签
    QLabel *p_controlLabel;         //J键的标签
    QLabel *r_controlLabel;         //C键的标签
    QLabel *esc_controlLabel;         //M键的标签
    QLabel *spaceLabel;             //空格的标签
    QLabel *scoreTitleLabel;        //分数标题标签
    QLabel *scoreLabel;             //分数标签（用来显示分数）
    QLabel *diffTitleLabel;
    QLabel *diffLabel;

signals:


};

#endif // MYMAIN_H
