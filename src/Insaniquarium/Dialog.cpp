#include "Dialog.h"
#include "ui_Dialog.h"
#include "ZObject/zscene.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <windows.h>
#include <QPushButton>
#include <climits>
#include <QPalette>
#include "gameinterface.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setStyleSheet("background-image: url(:/image/image/initPage.jpg);");
    btn1=new QPushButton(this);
    btn1->setGeometry(280,644,400,50);
    btn1->hide();
    btn2=new QPushButton(this);
    btn2->setGeometry(556,68,343,108);
    btn2->hide();
    this->setMouseTracking(true);
    timer=new QTimer();
    bar=new QProgressBar(this);
    bar->setGeometry(250,580,495,50);
    bar->hide();
    bar->setValue(0);
    connect(timer,SIGNAL(timeout()),this,SLOT(changeValue()));
    connect(timer,SIGNAL(destroyed()),this,SLOT(chooseGameMode()));
}

void Dialog::initGame(){
    this->setStyleSheet("background-image: url(:/image/image/loading.jpg);");
    timer->start(30);
    bar->show();
}

void Dialog::mouseMoveEvent(QMouseEvent *event){
    QPoint mousepos=event->pos();
    if(isInitPage){
        if(mousepos.rx()>=btn1->x() && mousepos.rx()<=btn1->x()+btn1->width()
                && mousepos.ry()>=btn1->y() && mousepos.ry()<=btn1->y()+btn1->height()){
            this->setCursor(Qt::PointingHandCursor);
        }else{
            this->setCursor(Qt::ArrowCursor);
        }
    }if(isChooseGameModePage){
        if(mousepos.rx()>=btn2->x() && mousepos.rx()<=btn2->x()+btn2->width()
                && mousepos.ry()>=btn2->y() && mousepos.ry()<=btn2->y()+btn2->height()){
            this->setCursor(Qt::PointingHandCursor);
        }else{
            this->setCursor(Qt::ArrowCursor);
        }
    }


}

void Dialog::mousePressEvent(QMouseEvent *event){    
    if(isInitPage){
        QPoint mousepos=event->pos();
        if(mousepos.rx()>=btn1->x() && mousepos.rx()<=btn1->x()+btn1->width()
                && mousepos.ry()>=btn1->y() && mousepos.ry()<=btn1->y()+btn1->height()){
            isInitPage=false;
            this->setCursor(Qt::ArrowCursor);
            delete btn1;
            btn1=nullptr;
            this->initGame();
        }
    }
    if(isChooseGameModePage){
        QPoint mousepos=event->pos();
        if(mousepos.rx()>=btn2->x() && mousepos.rx()<=btn2->x()+btn2->width()
                && mousepos.ry()>=btn2->y() && mousepos.ry()<=btn2->y()+btn2->height()){
            isChooseGameModePage=false;
            this->setCursor(Qt::ArrowCursor);
            delete btn2;
            btn2=nullptr;
            this->startGame();
        }
    }
}

void Dialog::changeValue(){
    if((bar->value()+10)>100){
        timer->stop();
        delete timer;
        timer=nullptr;
        isChooseGameModePage=true;
    }else{
        bar->setValue(bar->value()+10);
    }
}

void Dialog::chooseGameMode(){
    delete bar;
    bar=nullptr;
    this->setStyleSheet("background-image: url(:/image/image/chooseGameMode.jpg);");
}

void Dialog::startGame(){
    GameInterface* game_interface=new GameInterface();
    game_interface->show();
    this->close();
}

Dialog::~Dialog(){
    delete ui;
}


