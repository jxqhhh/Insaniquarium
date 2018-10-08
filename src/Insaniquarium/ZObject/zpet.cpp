#include "zpet.h"
#include "zscene.h"
#include <cmath>
#include <QDebug>
#include <climits>

inline int random(int x=360){
    if(x>0){
        return rand()%x;
    }else{
        return rand()%360;
    }
}

ZPet::ZPet(ZObject* parent,GameWidget* widget):ZObject(parent,widget){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    scene->petList.append(this);
}

ZPet::~ZPet()
{

}

void ZPet::shift(){

}

ZSnail::ZSnail(ZObject *parent, GameWidget *widget):ZPet(parent,widget){
    this->setGeometry(50,555,80,80);
    QPixmap pixmap(":/image/image/snail.png");
    this->setPixmap(pixmap);
    this->show();
}

void ZSnail::shift(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    int lowest_money_index=-1;
    int distance=-1;
    for(int i=0;i!=scene->moneyList.count();i++){
        if(scene->moneyList.at(i)->y()>distance){
            distance=scene->moneyList.at(i)->y();
            lowest_money_index=i;
        }
    }
    if(lowest_money_index==-1){
        return;
    }
    int x=this->x();
    int x_money=scene->moneyList.at(lowest_money_index)->x();
    if(pow(x-x_money,2)<=pow(speed,2)+0.5){
        this->move(x_money,this->y());
    }else if(x_money>x){
        this->move(this->x()+speed,this->y());
    }else{
        this->move(this->x()-speed,this->y());
    }
}

ZOyster::ZOyster(ZObject *parent, GameWidget *widget):ZPet(parent,widget){
    this->setGeometry(165,370,80,80);
    QPixmap pixmap(":/image/image/oyster.png");
    this->setPixmap(pixmap);
    this->show();
}

void ZOyster::shift(){
    if(pearlTakenAway){
        pearlTakenAway=false;
        pearlAvailable=false;
        QPixmap pixmap(":/image/image/oyster.png");
        this->setPixmap(pixmap);
        epoch_before_new_pearl=0;
        qDebug("new oyster");
    }
    if(!pearlAvailable){
        epoch_before_new_pearl++;
        epoch_before_new_pearl=epoch_before_new_pearl%4000;
        if(epoch_before_new_pearl==0){
            pearlAvailable=true;
            pearlTakenAway=false;
            epoch_before_new_pearl=0;
            QPixmap pixmap(":/image/image/oyster_with_pearl.png");
            this->setPixmap(pixmap);
            qDebug()<<"new pearl";
        }
    }
}

bool ZOyster::isPearlAvailable() const{
    return pearlAvailable;
}

void ZOyster::pearlCollected(){
    pearlTakenAway=true;
    pearlAvailable=false;
}

ZItchy::ZItchy(ZObject *parent, GameWidget *widget):ZPet(parent,widget){
    this->setGeometry(50,555,80,80);
    QPixmap pixmap(":/image/image/Itchy.png");
    this->setPixmap(pixmap);
    this->show();
}


void ZItchy::shift(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    num_interval++;
    num_interval=num_interval%5;
    if(num_interval!=0){
        return;
    }
    bool balrogAvailable=false;
    for(int i=0;i!=scene->alienList.count();i++){
        if(dynamic_cast<ZBalrog*>(scene->alienList[i])!=NULL){
            balrogAvailable=true;
            break;
        }
    }
    if(!balrogAvailable){
        this->go_to_move();
        return;
    }
    speed=8;
    int nearestBalrogIndex=-1;
    int distance=INT_MAX;
    for(int i=0;i!=scene->alienList.count();i++){
        if(dynamic_cast<ZBalrog*>(scene->alienList[i])==NULL){
            continue;
        }
        if(sqrt(pow(this->x()-scene->alienList.at(i)->x(),2)+pow(this->y()-scene->alienList.at(i)->y(),2))<distance){
            distance=sqrt(pow(this->x()-scene->alienList.at(i)->x(),2)+pow(this->y()-scene->alienList.at(i)->y(),2));
            nearestBalrogIndex=i;
        }
    }
    if(nearestBalrogIndex==-1){
        return;
    }
    if(distance<50){
        dynamic_cast<ZBalrog*>(scene->alienList[nearestBalrogIndex])->hitten();
    }
    if(distance<speed){
        this->move(scene->alienList.at(nearestBalrogIndex)->x(),scene->alienList.at(nearestBalrogIndex)->y());
    }else{
        this->move(this->x()+(speed+0.00001)/(distance+0.00001)*(scene->alienList.at(nearestBalrogIndex)->x()-this->x()),this->y()+(speed+0.00001)/(distance+0.00001)*(scene->alienList.at(nearestBalrogIndex)->y()-this->y()));
    }
}

void ZItchy::go_to_move(){
    speed=4;
    if(this->x() < 40 && this->y() + this->height() + 40 < 659 && this->y() > 40){
        angle=random(180)-90;
        this->move(this->x()+4,this->y()+3);
    }else if(this->x() + this->width() + 40 > 995 && this->y() + this->height() + 40 < 659 && this->y() > 40){
        angle=random(180)+90;
        this->move(this->x()-4,this->y()+3);
    }else if(this->x() < 40 && this->y() + this->height() + 40 > 659){
        angle=random(90)-90;
        this->move(this->x()+4,this->y()-3);
    }else if(this->x() + this->width() + 40 > 995 && this->y() + this->height() + 40 > 659){
        angle=random(90)+180;
        this->move(this->x()-4,this->y()+3);
    }else if(this->x() > 40  && this->x() + this->width() + 40 < 995 && this->y() + this->height() + 40 > 659){
        angle=random(180)+180;
        this->move(this->x()+4,this->y()-4);
    }else if(this->x() > 40  && this->x() + this->width() + 40 < 995 && this->y() < 40){
        angle=random(180);
        this->move(this->x()+4,this->y()+3);
    }else if(this->x() < 40 && this->y() < 40){
        angle=random(90);
        this->move(this->x()+4,this->y()+3);
    }else if(this->y() < 40 && this->x() + this->width() + 40 > 995){
        angle=random(90)+90;
        this->move(this->x()-4,this->y()+3);
    }else{
        int result=random(30);
        if(result==3){
            angle=random(360);
        }
        this->move(this->x()+speed*cos(angle),this->y()+speed*sin(angle));
    }
}
