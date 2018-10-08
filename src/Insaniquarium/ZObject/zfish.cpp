#include "zfish.h"
#include <cmath>
#include<cstdio>
#include<cstdlib>
#include <QDebug>
#include <string>
#include "zscene.h"
#include <climits>
#include "zfood.h"
#include "zmoney.h"

using std::cos;
using std::sin;

inline int random(int x=360){
    if(x>0){
        return rand()%x;
    }else{
        return rand()%360;
    }
}

ZFish::ZFish(ZObject* parent,GameWidget* widget):ZObject(parent,widget){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    scene->fishList.append(this);
}

ZFish::~ZFish()
{

}

bool ZFish::hungry() const{
    return isHungry;
}

void ZFish::eaten(){

}

void ZFish::eatFood(int food_energy){

}

int ZFish::get_X() const{
    return this->x();
}

int ZFish::get_Y() const{
    return this->y();
}

bool ZFish::is_fed_on_fodder() const{
    return fed_on_fodder;
}

void ZFish::shift(){
    num_interval++;
    num_interval=num_interval%5;
    hungerValue++;
    this->update_state();//更新状态
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    this->go_to_move();
    eatenByMonster();
    if(!alive){
        return;
    }
    eaten();
    produce();
}

void ZGuppy::go_to_move(){
    if(num_interval==0){
        bool foodAvailable=isFoodAvailable();
        if(isGoingToEat){//如果之前在捕食状态，当前依然会继续之前的捕食状态
            if(isHungry){
                speed=10;
            }else{
                speed=6;
            }
            this->go_to_eat();
        }
        //如果之前不在捕食状态，对鱼如何移动进行判定
        if(isHungry && foodAvailable){//如果饥饿并且有食物，go_to_eat
            speed=10;//饥饿时进食速度更快
            this->go_to_eat();
        }else if(foodAvailable){//如果有食物但是不饥饿，有三分之一的概率去吃食物
            int tmp=random(10);
            if(tmp==2){
                speed=6;//不饥饿时进食速度慢
                this->go_to_eat();
            }else{
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
        }else{
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
    }
}

ZGuppy::ZGuppy(ZObject *parent, GameWidget *widget,int x_init,int y_init):ZFish(parent,widget){
    this->setGeometry(x_init,y_init,80,80);
    QPixmap pixmap(":/image/image/small_guppy_swim.png");
    this->setPixmap(pixmap);
    this->show();
    currentState=SmallGuppy;
    currentPixmapIndex=0;
}

void ZGuppy::update_state(){
    if(hungerValue>max_HungerValue){
        this->alive=false;
        this->isHungry=true;
    }else if(hungerValue>min_HungerValue){
        this->isHungry=true;
    }else{
        this->isHungry=false;
    }
    if(energy<=min_energy_for_MidGuppy){
        currentState=SmallGuppy;
    }else if(energy<=min_energy_for_LargeGuppy){
        currentState=MidGuppy;
    }else if(currentState!=GuppyKing && currentState!=LargeGuppy){
        currentState=LargeGuppy;
    }else{
        int tmp=random(80000);
        if(tmp==3000){
            currentState=GuppyKing;
        }
    }
    if(!isHungry){
        switch(currentState){
            case(SmallGuppy):{
                if(currentPixmapIndex==0){
                    break;
                }
                currentPixmapIndex=0;
                QPixmap pixmap(":/image/image/small_guppy_swim.png");
                this->setPixmap(pixmap);
                break;
            }
            case(MidGuppy):{
                if(currentPixmapIndex==1){
                    break;
                }
                currentPixmapIndex=1;
                QPixmap pixmap(":/image/image/mid_guppy_swim.png");
                this->setPixmap(pixmap);
                break;
            }
            case(LargeGuppy):{
                if(currentPixmapIndex==2){
                    break;
                }
                currentPixmapIndex=2;
                QPixmap pixmap(":/image/image/large_guppy_swim.png");
                this->setPixmap(pixmap);
                break;
            }
            case(GuppyKing):{
                if(currentPixmapIndex==3){
                    break;
                }
                currentPixmapIndex=3;
                QPixmap pixmap(":/image/image/guppy_king_swim.png");
                this->setPixmap(pixmap);
                break;
            }
        }
    }else if(hungerValue<=5800){
        switch(currentState){
            case(SmallGuppy):{
                if(currentPixmapIndex==4){
                    break;
                }
                currentPixmapIndex=4;
                QPixmap pixmap(":/image/image/small_guppy_hungry.png");
                this->setPixmap(pixmap);
                break;
            }
            case(MidGuppy):{
                if(currentPixmapIndex==5){
                    break;
                }
                currentPixmapIndex=5;
                QPixmap pixmap(":/image/image/mid_guppy_hungry.png");
                this->setPixmap(pixmap);
                break;
            }
            case(LargeGuppy):{
                if(currentPixmapIndex==6){
                    break;
                }
                currentPixmapIndex=6;
                QPixmap pixmap(":/image/image/large_guppy_hungry.png");
                this->setPixmap(pixmap);
                break;
            }
            case(GuppyKing):{
                if(currentPixmapIndex==7){
                    break;
                }
                currentPixmapIndex=7;
                QPixmap pixmap(":/image/image/guppy_king_hungry.png");
                this->setPixmap(pixmap);
                break;
            }
        }
    }else{
        switch(currentState){
            case(SmallGuppy):{
                if(currentPixmapIndex==8){
                    break;
                }
                currentPixmapIndex=8;
                QPixmap pixmap(":/image/image/small_guppy_die.png");
                this->setPixmap(pixmap);
                break;
            }
            case(MidGuppy):{
                if(currentPixmapIndex==9){
                    break;
                }
                currentPixmapIndex=9;
                QPixmap pixmap(":/image/image/mid_guppy_die.png");
                this->setPixmap(pixmap);
                break;
            }
            case(LargeGuppy):{
                if(currentPixmapIndex==10){
                    break;
                }
                currentPixmapIndex=10;
                QPixmap pixmap(":/image/image/large_guppy_die.png");
                this->setPixmap(pixmap);
                break;
            }
            case(GuppyKing):{
                if(currentPixmapIndex==11){
                    break;
                }
                currentPixmapIndex=11;
                QPixmap pixmap(":/image/image/guppy_king_die.png");
                this->setPixmap(pixmap);
                break;
            }
        }
    }

}



void ZFish::eatenByMonster(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    for(int i=0;i<scene->alienList.count();i++){
        double dist=sqrt(pow(this->x()-scene->alienList.at(i)->x(),2)+pow(this->y()-scene->alienList.at(i)->y(),2));
        if(dist<=30){
            if(random(20)!=2){
                return;
            }
            scene->alienList[i]->eatFood();
            this->alive=false;
            break;
        }
    }
}

void ZGuppy::eaten(){
    if(!isSmallGuppy()){
        return;
    }
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    for(int i=0;i<scene->fishList.count();i++){
        ZSmallCarnivorousFish* cfish=dynamic_cast<ZSmallCarnivorousFish*>(scene->fishList[i]);
        if(cfish==NULL){
            continue;
        }
        if(!cfish->hungry()){
            continue;
        }
        double dist=sqrt(pow(this->x()-scene->fishList.at(i)->x(),2)+pow(this->y()-scene->fishList.at(i)->y(),2));
        if(dist<=30){
            if(random(20)!=2){
                return;
            }
            cfish->eatFood();
            this->alive=false;
            break;
        }
    }
}

void ZGuppy::produce(){
    epoch_before_produce++;
    epoch_before_produce=epoch_before_produce%frequency_for_produce;
    if(epoch_before_produce>0){
        return;
    }
    if(currentState==SmallGuppy){
        return;
    }
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    if(currentState==MidGuppy){
        ZMoney* coin=new SilverCoin(this->parent,scene->widget,this->x()+0.5*this->width(),this->y()+0.2*this->height());
        return;
    }
    if(currentState==LargeGuppy){
        ZMoney* coin=new GoldenCoin(this->parent,scene->widget,this->x()+0.5*this->width(),this->y()+0.2*this->height());
        return;
    }
    if(currentState==GuppyKing){
        ZMoney* coin=new Diamond(this->parent,scene->widget,this->x()+0.5*this->width(),this->y()+0.2*this->height());
        return;
    }

}

bool ZGuppy::isFoodAvailable(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    return scene->foodList.count()>0;
}

void ZGuppy::go_to_eat(){
    int nearest_food_index=-1;
    int distance=INT_MAX;
    isGoingToEat=true;
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    for(int i=0;i!=scene->foodList.count();i++){
        int dist=sqrt(pow(this->x()-scene->foodList[i]->x(),2)+pow(this->y()-scene->foodList[i]->y(),2));
        if(dist<distance){
            distance=dist;
            nearest_food_index=i;
        }
    }
    if(nearest_food_index==-1){
        isGoingToEat=false;
        return;
    }else{
        if(distance<=speed){
            this->move(scene->foodList[nearest_food_index]->x(),scene->foodList[nearest_food_index]->y());
        }else{
            this->move(this->x()+(speed+0.00001)/(distance+0.00001)*(scene->foodList[nearest_food_index]->x()-this->x()),this->y()+(speed+0.00001)/(distance+0.00001)*(scene->foodList[nearest_food_index]->y()-this->y()));
        }
    }
}

void ZGuppy::eatFood(int food_energy){
    isHungry=false;
    hungerValue=0;
    alive=true;
    isGoingToEat=false;
    energy+=food_energy;
}

bool ZGuppy::isSmallGuppy(){
    return currentState==SmallGuppy;
}

void ZGuppyMom::go_to_move(){
    if(num_interval==0){
        bool foodAvailable=isFoodAvailable();
        if(isGoingToEat){//如果之前在捕食状态，当前依然会继续之前的捕食状态
            if(isHungry){
                speed=10;
            }else{
                speed=6;
            }
            this->go_to_eat();
        }
        //如果之前不在捕食状态，对鱼如何移动进行判定
        if(isHungry && foodAvailable){//如果饥饿并且有食物，go_to_eat
            speed=10;//饥饿时进食速度更快
            this->go_to_eat();
        }else if(foodAvailable){//如果有食物但是不饥饿，有三分之一的概率去吃食物
            int tmp=random(10);
            if(tmp==2){
                speed=6;//不饥饿时进食速度慢
                this->go_to_eat();
            }else{
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
        }else{
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
    }
}

ZGuppyMom::ZGuppyMom(ZObject *parent, GameWidget *widget, int x_init, int y_init):ZFish(parent,widget){
    this->setGeometry(x_init,y_init,80,80);
    QPixmap pixmap(":/image/image/small_guppyMom_swim.png");
    this->setPixmap(pixmap);
    this->show();
    currentState=SmallGuppyMom;
    currentPixmapIndex=0;
}

void ZGuppyMom::go_to_eat(){
    int nearest_food_index=-1;
    int distance=INT_MAX;
    isGoingToEat=true;
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    for(int i=0;i!=scene->foodList.count();i++){
        int dist=sqrt(pow(this->x()-scene->foodList[i]->x(),2)+pow(this->y()-scene->foodList[i]->y(),2));
        if(dist<distance){
            distance=dist;
            nearest_food_index=i;
        }
    }
    if(nearest_food_index==-1){
        isGoingToEat=false;
        return;
    }else{
        if(distance<=speed){
            this->move(scene->foodList[nearest_food_index]->x(),scene->foodList[nearest_food_index]->y());
        }else{
            this->move(this->x()+(speed+0.00001)/(distance+0.00001)*(scene->foodList[nearest_food_index]->x()-this->x()),this->y()+(speed+0.00001)/(distance+0.00001)*(scene->foodList[nearest_food_index]->y()-this->y()));
        }
    }
}

bool ZGuppyMom::isFoodAvailable(){    
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    return scene->foodList.count()>0;
}

void ZGuppyMom::update_state(){
    if(hungerValue>max_HungerValue){
        this->alive=false;
        this->isHungry=true;
    }else if(hungerValue>min_HungerValue){
        this->isHungry=true;
    }else{
        this->isHungry=false;
    }
    if(energy<=min_energy_for_LargeGuppyMom){
        currentState=SmallGuppyMom;
    }else{
        currentState=LargeGuppyMom;
    }
    if(!isHungry){
        switch(currentState){
            case(SmallGuppyMom):{
                if(currentPixmapIndex==0){
                    break;
                }
                currentPixmapIndex=0;
                QPixmap pixmap(":/image/image/small_guppyMom_swim.png");
                this->setPixmap(pixmap);
                break;
            }
            case(LargeGuppyMom):{
                if(currentPixmapIndex==1){
                    break;
                }
                currentPixmapIndex=1;
                QPixmap pixmap(":/image/image/large_guppyMom_swim.png");
                this->setPixmap(pixmap);
                break;
            }
        }
    }else if(hungerValue<=5800){
        switch(currentState){
            case(SmallGuppyMom):{
                if(currentPixmapIndex==2){
                    break;
                }
                currentPixmapIndex=2;
                QPixmap pixmap(":/image/image/small_guppyMom_hungry.png");
                this->setPixmap(pixmap);
                break;
            }
            case(LargeGuppyMom):{
                if(currentPixmapIndex==3){
                    break;
                }
                currentPixmapIndex=3;
                QPixmap pixmap(":/image/image/large_guppyMom_hungry.png");
                this->setPixmap(pixmap);
                break;
            }
        }
    }else{
        switch(currentState){
            case(SmallGuppyMom):{
                if(currentPixmapIndex==4){
                    break;
                }
                currentPixmapIndex=4;
                QPixmap pixmap(":/image/image/small_guppyMom_die.png");
                this->setPixmap(pixmap);
                break;
            }
            case(LargeGuppyMom):{
                if(currentPixmapIndex==5){
                    break;
                }
                currentPixmapIndex=5;
                QPixmap pixmap(":/image/image/large_guppyMom_die.png");
                this->setPixmap(pixmap);
                break;
            }
        }
    }
}

void ZGuppyMom::produce(){
    epoch_before_produce++;
    if(currentState==SmallGuppyMom){
        epoch_before_produce=epoch_before_produce%frequency_for_SmallGuppyMom_produce;
    }else{
        epoch_before_produce=epoch_before_produce%frequency_for_LargeGuppyMom_produce;
    }
    if(epoch_before_produce>0){
        return;
    }
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    ZFish* smallGuppy=new ZGuppy(this->parent,scene->widget,this->x()+0.5*this->width(),this->y()+0.2*this->height());
}

void ZGuppyMom::eatFood(int food_energy){
    isHungry=false;
    hungerValue=0;
    alive=true;
    isGoingToEat=false;
    energy+=food_energy;
}

ZSmallCarnivorousFish::ZSmallCarnivorousFish(ZObject *parent, GameWidget *widget):ZFish(parent,widget){
    this->setGeometry(200,200,80,80);
    QPixmap pixmap(":/image/image/SmallCarnivorousFish.png");
    this->setPixmap(pixmap);
    this->show();
}

bool ZSmallCarnivorousFish::isFoodAvailable(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    for(int i=0;i<scene->fishList.count();i++){
        ZGuppy* g=dynamic_cast<ZGuppy*>(scene->fishList[i]);
        if(g!=NULL){
            if(g->isSmallGuppy()){
                return true;
            }
        }
    }
    return false;
}

void ZSmallCarnivorousFish::go_to_move(){
    if(num_interval!=0){
        return;
    }
    bool foodAvailable=isFoodAvailable();
    if(isHungry && foodAvailable){//如果饥饿并且有食物，go_to_eat
        speed=10;//饥饿时进食速度更快
        this->go_to_eat();
    }else{
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
}

void ZSmallCarnivorousFish::go_to_eat(){
    int nearest_small_guppy_index=-1;
    int distance=INT_MAX;
    speed=10;
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    for(int i=0;i!=scene->fishList.count();i++){
        ZGuppy* g=dynamic_cast<ZGuppy*>(scene->fishList[i]);
        if(g==NULL){
            continue;
        }
        if(!g->isSmallGuppy()){
            continue;
        }
        int dist=sqrt(pow(this->x()-g->x(),2)+pow(this->y()-g->y(),2));
        if(dist<distance){
            distance=dist;
            nearest_small_guppy_index=i;
        }
    }
    if(nearest_small_guppy_index==-1){
        return;
    }else{
        if(distance<=speed){
            this->move(scene->fishList[nearest_small_guppy_index]->x(),scene->fishList[nearest_small_guppy_index]->y());
        }else{
            this->move(this->x()+(speed+0.00001)/(distance+0.00001)*(scene->fishList[nearest_small_guppy_index]->x()-this->x()),this->y()+(speed+0.00001)/(distance+0.00001)*(scene->fishList[nearest_small_guppy_index]->y()-this->y()));
        }
    }
}

void ZSmallCarnivorousFish::update_state(){
    if(hungerValue>max_HungerValue){
        this->alive=false;
        this->isHungry=true;
    }else if(hungerValue>min_HungerValue){
        this->isHungry=true;
    }else{
        this->isHungry=false;
    }
    if(!isHungry){
        if(currentPixmapIndex!=0){
            currentPixmapIndex=0;
            QPixmap pixmap(":/image/image/SmallCarnivorousFish.png");
            this->setPixmap(pixmap);
        }
    }else if(hungerValue<=6600){
        if(currentPixmapIndex!=1){
            currentPixmapIndex=1;
            QPixmap pixmap(":/image/image/SmallCarnivorousFishHungry.png");
            this->setPixmap(pixmap);
        }
    }else{
        if(currentPixmapIndex!=2){
            currentPixmapIndex=2;
            QPixmap pixmap(":/image/image/SmallCarnivorousFishDie.png");
            this->setPixmap(pixmap);
        }
    }
}

void ZSmallCarnivorousFish::eatFood(){
    this->hungerValue=0;
    this->isHungry=false;
}

void ZSmallCarnivorousFish::produce(){
    epoch_before_produce++;
    epoch_before_produce=epoch_before_produce%frequency_for_produce;
    if(epoch_before_produce==0){
        ZScene* scene=dynamic_cast<ZScene*>(this->parent);
        new Diamond(scene,scene->widget,this->x()+0.5*this->width(),this->y()+0.2*this->height());
    }
}

void ZSmallCarnivorousFish::eaten(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    for(int i=0;i<scene->fishList.count();i++){
        ZLargeCarnivorousFish* cfish=dynamic_cast<ZLargeCarnivorousFish*>(scene->fishList[i]);
        if(cfish==NULL){
            continue;
        }
        if(!cfish->hungry()){
            continue;
        }
        double dist=sqrt(pow(this->x()-scene->fishList.at(i)->x(),2)+pow(this->y()-scene->fishList.at(i)->y(),2));
        if(dist<=30){
            if(random(20)!=2){
                return;
            }
            cfish->eatFood();
            this->alive=false;
            break;
        }
    }
}

ZLargeCarnivorousFish::ZLargeCarnivorousFish(ZObject *parent, GameWidget *widget):ZFish(parent,widget){
    this->setGeometry(200,200,160,160);
    QPixmap pixmap(":/image/image/LargeCarnivorousFish.png");
    this->setPixmap(pixmap);
    this->show();
}

void ZLargeCarnivorousFish::go_to_eat(){
    int nearest_small_carnivorous_fish_index=-1;
    int distance=INT_MAX;
    speed=10;
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    for(int i=0;i!=scene->fishList.count();i++){
        ZSmallCarnivorousFish* g=dynamic_cast<ZSmallCarnivorousFish*>(scene->fishList[i]);
        if(g==NULL){
            continue;
        }
        int dist=sqrt(pow(this->x()-g->x(),2)+pow(this->y()-g->y(),2));
        if(dist<distance){
            distance=dist;
            nearest_small_carnivorous_fish_index=i;
        }
    }
    if(nearest_small_carnivorous_fish_index==-1){
        return;
    }else{
        if(distance<=speed){
            this->move(scene->fishList[nearest_small_carnivorous_fish_index]->x(),scene->fishList[nearest_small_carnivorous_fish_index]->y());
        }else{
            this->move(this->x()+(speed+0.00001)/(distance+0.00001)*(scene->fishList[nearest_small_carnivorous_fish_index]->x()-this->x()),this->y()+(speed+0.00001)/(distance+0.00001)*(scene->fishList[nearest_small_carnivorous_fish_index]->y()-this->y()));
        }
    }
}

bool ZLargeCarnivorousFish::isFoodAvailable(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    for(int i=0;i<scene->fishList.count();i++){
        ZSmallCarnivorousFish* g=dynamic_cast<ZSmallCarnivorousFish*>(scene->fishList[i]);
        if(g!=NULL){
            return true;
        }
    }
    return false;
}

void ZLargeCarnivorousFish::update_state(){
    if(hungerValue>max_HungerValue){
        this->alive=false;
        this->isHungry=true;
    }else if(hungerValue>min_HungerValue){
        this->isHungry=true;
    }else{
        this->isHungry=false;
    }
    if(!isHungry){
        if(currentPixmapIndex!=0){
            currentPixmapIndex=0;
            QPixmap pixmap(":/image/image/LargeCarnivorousFish.png");
            this->setPixmap(pixmap);
        }
    }else if(hungerValue<=6600){
        if(currentPixmapIndex!=1){
            currentPixmapIndex=1;
            QPixmap pixmap(":/image/image/LargeCarnivorousFishHungry.png");
            this->setPixmap(pixmap);
        }
    }else{
        if(currentPixmapIndex!=2){
            currentPixmapIndex=2;
            QPixmap pixmap(":/image/image/LargeCarnivorousFishDie.png");
            this->setPixmap(pixmap);
        }
    }
}

void ZLargeCarnivorousFish::produce(){
    epoch_before_produce++;
    epoch_before_produce=epoch_before_produce%frequency_for_produce;
    if(epoch_before_produce==0){
        ZScene* scene=dynamic_cast<ZScene*>(this->parent);
        new JewelBox(scene,scene->widget,this->x()+0.5*this->width(),this->y()+0.2*this->height());
    }
}

void ZLargeCarnivorousFish::go_to_move(){
    if(num_interval!=0){
        return;
    }
    bool foodAvailable=isFoodAvailable();
    if(isHungry && foodAvailable){//如果饥饿并且有食物，go_to_eat
        speed=10;//饥饿时进食速度更快
        this->go_to_eat();
    }else{
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
}

void ZLargeCarnivorousFish::eatFood(){
    this->hungerValue=0;
    this->isHungry=false;
}
