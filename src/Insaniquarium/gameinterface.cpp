#include "gameinterface.h"
#include "ui_gameinterface.h"
#include <QMouseEvent>
#include <QDebug>

GameInterface::GameInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameInterface)
{
    ui->setupUi(this);
    widget = new GameWidget(this);
    widget->setAutoFillBackground(true);
    QPixmap pixmap(":/image/image/aquarium1.jpg");
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(0,85,995,659);
    widget->raise();
    QPalette palette;
    palette.setBrush(widget->backgroundRole(), QBrush(pixmap));
    widget->setPalette(palette);
    scene=new ZLevel1(nullptr,widget);
    connect(widget,SIGNAL(mousePressed(int,int)),scene,SLOT(processMousePressed(int,int)));
    connect(scene,SIGNAL(moneyCollected(int)),this,SLOT(moneyCollected(int)));
}

GameInterface::~GameInterface()
{
    delete ui;
    if(scene!=nullptr){
        delete scene;
        scene=nullptr;

    }
}

void GameInterface::moneyCollected(int money){
    total_money+=money;
    ui->lcdNumber->display(total_money);
}



void GameInterface::on_buy_new_guppy_clicked(){
    if(this->total_money>=100){
        total_money-=100;
        ui->lcdNumber->display(total_money);
        ZFish* guppy=new ZGuppy(this->scene,this->widget,50,50);
    }
}

void GameInterface::on_upgrade_food_clicked()
{
    if(currentFoodLevel==foodLevel1 && currentLevel>=level2){
        if(total_money<200){
            return;
        }
        total_money-=200;
        ui->lcdNumber->display(total_money);
        currentFoodLevel=foodLevel2;
        max_num_of_food=1;
        ui->num_of_food->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/max_food_num_2.png);"));
        this->scene->upgrade_food();
        return;
    }
}


void GameInterface::on_buy_new_guppyMom_clicked(){
    if(this->total_money>=200){
        total_money-=200;
        ui->lcdNumber->display(total_money);
        ZFish* guppy=new ZGuppyMom(this->scene,this->widget,50,50);
    }
}

void GameInterface::on_buy_egg_clicked(){
    switch(currentLevel){
        case(level1):{
            if(this->total_money>=150){
                total_money-=150;
                ui->lcdNumber->display(total_money);
                currentEggNum+=1;
                switch(currentEggNum){
                    case(1):
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/buy_egg_2.png);"));
                        break;
                    case(2):
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/buy_egg_3.png);"));
                        break;
                    case(3):
                        this->scene->removeAll();
                        currentLevel+=1;
                        total_money=0;
                        ui->lcdNumber->display(0);
                        this->startNewLevel(currentLevel);
                        currentEggNum=0;
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/level2_buy_egg_1.png);"));
                        break;
                }
            }
            break;
        }
        case(level2):{
            if(this->total_money>=500){
                total_money-=500;
                ui->lcdNumber->display(total_money);
                currentEggNum+=1;
                switch(currentEggNum){
                    case(1):
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/level2_buy_egg_2.png);"));
                        break;
                    case(2):
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/level2_buy_egg_3.png);"));
                        break;
                    case(3):
                        this->scene->removeAll();
                        currentLevel+=1;
                        total_money=0;
                        ui->lcdNumber->display(0);
                        this->startNewLevel(currentLevel);
                        currentEggNum=0;
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/level3_buy_egg_1.png);"));
                        break;
                }
            }
            break;
        }
        case(level3):{
            if(this->total_money>=2000){
                total_money-=2000;
                ui->lcdNumber->display(total_money);
                currentEggNum+=1;
                switch(currentEggNum){
                    case(1):
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/level3_buy_egg_2.png);"));
                        break;
                    case(2):
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/level3_buy_egg_3.png);"));
                        break;
                    case(3):
                        this->scene->removeAll();
                        currentLevel+=1;
                        total_money=0;
                        ui->lcdNumber->display(0);
                        this->startNewLevel(currentLevel);
                        currentEggNum=0;
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/level4_buy_egg_1.png);"));
                        break;
                }
            }
            break;
        }
        case(level4):{
            if(this->total_money>=3000){
                total_money-=3000;
                ui->lcdNumber->display(total_money);
                currentEggNum+=1;
                switch(currentEggNum){
                    case(1):
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/level4_buy_egg_2.png);"));
                        break;
                    case(2):
                        ui->buy_egg->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/level4_buy_egg_3.png);"));
                        break;
                    case(3):
                        this->scene->removeAll();
                        currentLevel+=1;
                        total_money=0;
                        ui->lcdNumber->display(0);
                        currentEggNum=0;
                        break;
                }
            }
            break;
        }
    }
}

void GameInterface::winGame(){

}

void GameInterface::startNewLevel(int newLevel){

    ui->upgrade_food->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/upgrade_food.png);"));
    ui->num_of_food->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/default_toolbar_icon.png);"));
    currentFoodLevel=foodLevel1;
    max_num_of_food=1;
    switch (currentLevel) {
    case level2:{
        break;
    }
    case level3:{
        ui->buy_small_carnivorous_fish->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/buy_small_carnivorous_fish.png);"));        
        ui->buy_large_carnivorous_fish->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/buy_large_carnivorous_fish.png);"));
        break;
    }
    case level4:{
        break;
    }
    }
}

void GameInterface::on_num_of_food_clicked()
{
    if(currentFoodLevel>=foodLevel2 && max_num_of_food<=5){
        if(total_money<300){
            return;
        }
        total_money-=300;
        ui->lcdNumber->display(total_money);
        max_num_of_food++;
        switch (max_num_of_food) {
        case 2:
            ui->num_of_food->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/max_food_num_3.png);"));
            this->scene->upgrade_food();
            break;
        case 3:
            ui->num_of_food->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/max_food_num_4.png);"));
            this->scene->upgrade_food();
            break;
        case 4:
            ui->num_of_food->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/max_food_num_5.png);"));
            this->scene->upgrade_food();
            break;
        case 5:
            ui->num_of_food->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/max_food_num_6.png);"));
            this->scene->upgrade_food();
            break;
        case 6:
            ui->num_of_food->setStyleSheet(QString::fromUtf8("background-image: url(:/image/image/max_food_num.png);"));
            this->scene->upgrade_food();
            break;
        default:
            break;
        }
    }
}

void GameInterface::on_buy_small_carnivorous_fish_clicked()
{
    if(currentLevel>=level3){
        if(this->total_money>=1000){
            total_money-=1000;
            ui->lcdNumber->display(total_money);
            new ZSmallCarnivorousFish(this->scene,this->widget);
        }
    }
}

void GameInterface::on_buy_large_carnivorous_fish_clicked()
{
    if(currentLevel>=level3){
        if(this->total_money>=10000){
            total_money-=10000;
            ui->lcdNumber->display(total_money);
            new ZLargeCarnivorousFish(this->scene,this->widget);
        }
    }
}
