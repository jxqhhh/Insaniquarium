#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QMouseEvent>
#include "ZObject/zfish.h"
#include <QLabel>

GameWidget::GameWidget(QWidget *parent):QWidget(parent),ui(new Ui::GameWidget){
    ui->setupUi(this);
    /*QLabel* label=new QLabel(this);
    label->setGeometry(QRect(150, 585, 695, 51));
    QFont font;
    font.setPointSize(20);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    label->setText(QString::fromStdString("DARK BLUE MONSTER APPROACHING"));
    label->show();*/
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::mousePressEvent(QMouseEvent *e){
    QPoint mousepos=e->pos();
    int x=mousepos.x();
    int y=mousepos.y();
    emit mousePressed(x,y);
}
