#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

namespace Ui {
class GameWidget;
}

class GameWidget;

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent);
    ~GameWidget();
    void mousePressEvent(QMouseEvent *e);
    void startLevel2();
signals:
    void mousePressed(int x,int y);
private:
    Ui::GameWidget *ui;
};

#endif // GAMEWIDGET_H
