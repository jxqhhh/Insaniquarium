#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMovie>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QProgressBar>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::Dialog *ui;
    QPushButton* btn1;//对应于初始界面(initPage.jpg)的"click here to play"按钮
    bool isInitPage=true;//表示当前界面是否为初始界面
    QTimer* timer;//计时器，用于控制进度条(QProgressBar* bar)
    QProgressBar* bar;//对应于游戏加载界面的进度条
    bool isChooseGameModePage=false;//表示当前界面是否为游戏模式选择界面(chooseGameMode.jpg)
    QPushButton* btn2;//对应于游戏模式选择界面的"Start Adventure"按钮
    void startGame();//开始游戏
    void initGame();//加载初始界面
private slots:
    void changeValue();
    void chooseGameMode();//加载游戏模式选择界面
};

#endif //
