#include "zalien.h"
#include "zscene.h"
#include "zmoney.h"
#include <climits>
#include <cmath>
#include <cstdlib>

ZAlien::ZAlien(ZObject* parent,GameWidget* widget):ZObject(parent,widget){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    scene->alienList.append(this);
}

ZAlien::~ZAlien()
{

}

void ZAlien::shift(){

}

ZDarkBlueMonster::ZDarkBlueMonster(ZObject* parent,GameWidget* widget):ZAlien(parent,widget){
    HP=5;
    this->setGeometry(100,100,160,160);
    QPixmap pixmap(":/image/image/DarkBlueMonster.png");
    this->setPixmap(pixmap);
    this->show();
}

void ZDarkBlueMonster::shift(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    if(HP<=0){
        this->alive=false;
        new Diamond(this->parent,scene->widget,this->x()+0.5*this->width(),this->y()+0.2*this->height());
    }
    int tmp=rand()%6;
    if(tmp!=2){
        return;
    }
    if(scene->fishList.count()==0){
        int angle=rand()%360;
        this->move(this->x()+cos(angle),this->y()+sin(angle));
    }
    int nearestFishIndex=-1;
    int distance=INT_MAX;
    for(int i=0;i!=scene->fishList.count();i++){
        if(sqrt(pow(this->x()-scene->fishList.at(i)->x(),2)+pow(this->y()-scene->fishList.at(i)->y(),2))<distance){
            distance=sqrt(pow(this->x()-scene->fishList.at(i)->x(),2)+pow(this->y()-scene->fishList.at(i)->y(),2));
            nearestFishIndex=i;
        }
    }
    if(nearestFishIndex==-1){
        return;
    }
    if(distance<speed){
        this->move(scene->fishList.at(nearestFishIndex)->x(),scene->fishList.at(nearestFishIndex)->y());
    }else{
        this->move(this->x()+(speed+0.00001)/(distance+0.00001)*(scene->fishList.at(nearestFishIndex)->x()-this->x()),this->y()+(speed+0.00001)/(distance+0.00001)*(scene->fishList.at(nearestFishIndex)->y()-this->y()));
    }
}

void ZDarkBlueMonster::eatFood(){

}

void ZAlien::hitten(bool go_to_right,bool go_to_bottom){
    if(dynamic_cast<ZDarkBlueMonster*>(this)!=NULL){
        HP--;
    }
    if(go_to_right){
        int x=this->x()+30<965?this->x()+30:965;
        this->move(x,this->y());
    }else{
        int x=this->x()-30>10?this->x()-30:10;
        this->move(x,this->y());
    }
    if(go_to_bottom){
        int y=this->y()+30<629?this->y()+30:629;
        this->move(this->x(),y);
    }else{
        int y=this->y()-30>10?this->y()-30:10;
        this->move(this->x(),y);
    }
}

ZGluttonousMonster::ZGluttonousMonster(ZObject *parent, GameWidget *widget):ZAlien(parent,widget){
    HP=4;
    this->setGeometry(150,150,160,160);
    QPixmap pixmap(":/image/image/GluttonousMonster.png");
    this->setPixmap(pixmap);
    this->show();
}

void ZGluttonousMonster::shift(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    if(HP<=0){
        this->alive=false;
        new Diamond(this->parent,scene->widget,this->x()+0.5*this->width(),this->y()+0.2*this->height());
    }
    int tmp=rand()%6;
    if(tmp!=2){
        return;
    }
    if(scene->fishList.count()==0 && scene->foodList.count()==0){
        int angle=rand()%360;
        this->move(this->x()+cos(angle),this->y()+sin(angle));
    }
    int nearestFishIndex=-1;
    int nearestFoodIndex=-1;
    int min_distance_away_from_fish=INT_MAX;
    int min_distance_away_from_food=INT_MAX;
    for(int i=0;i!=scene->fishList.count();i++){
        if(sqrt(pow(this->x()-scene->fishList.at(i)->x(),2)+pow(this->y()-scene->fishList.at(i)->y(),2))<min_distance_away_from_fish){
            min_distance_away_from_fish=sqrt(pow(this->x()-scene->fishList.at(i)->x(),2)+pow(this->y()-scene->fishList.at(i)->y(),2));
            nearestFishIndex=i;
        }
    }
    for(int i=0;i!=scene->foodList.count();i++){
        if(sqrt(pow(this->x()-scene->foodList.at(i)->x(),2)+pow(this->y()-scene->foodList.at(i)->y(),2))<min_distance_away_from_food){
            min_distance_away_from_food=sqrt(pow(this->x()-scene->foodList.at(i)->x(),2)+pow(this->y()-scene->foodList.at(i)->y(),2));
            nearestFoodIndex=i;
        }
    }
    if(nearestFishIndex==-1 && nearestFoodIndex==-1){
        return;
    }
    if(min_distance_away_from_fish<min_distance_away_from_food){
        if(min_distance_away_from_fish<speed){
            this->move(scene->fishList.at(nearestFishIndex)->x(),scene->fishList.at(nearestFishIndex)->y());
        }else{
            this->move(this->x()+(speed+0.00001)/(min_distance_away_from_fish+0.00001)*(scene->fishList.at(nearestFishIndex)->x()-this->x()),this->y()+(speed+0.00001)/(min_distance_away_from_fish+0.00001)*(scene->fishList.at(nearestFishIndex)->y()-this->y()));
        }
    }else{
        if(min_distance_away_from_food<speed){
            this->move(scene->foodList.at(nearestFoodIndex)->x(),scene->foodList.at(nearestFoodIndex)->y());
        }else{
            this->move(this->x()+(speed+0.00001)/(min_distance_away_from_food+0.00001)*(scene->foodList.at(nearestFoodIndex)->x()-this->x()),this->y()+(speed+0.00001)/(min_distance_away_from_food+0.00001)*(scene->foodList.at(nearestFoodIndex)->y()-this->y()));
        }
    }
    
}

void ZGluttonousMonster::eatFood(){
    HP--;
}

ZBalrog::ZBalrog(ZObject *parent, GameWidget *widget):ZAlien(parent,widget){
    this->setGeometry(100,100,160,160);
    QPixmap pixmap(":/image/image/Balrog.png");
    this->setPixmap(pixmap);
    this->show();
    HP=100;
}

void ZBalrog::shift(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    if(HP<=0){
        this->alive=false;
        new Diamond(this->parent,scene->widget,this->x()+0.5*this->width(),this->y()+0.2*this->height());
        return;
    }
    int tmp=rand()%6;
    if(tmp!=2){
        return;
    }
    if(scene->fishList.count()==0){
        int angle=rand()%360;
        this->move(this->x()+cos(angle),this->y()+sin(angle));
    }
    int nearestFishIndex=-1;
    int distance=INT_MAX;
    for(int i=0;i!=scene->fishList.count();i++){
        if(sqrt(pow(this->x()-scene->fishList.at(i)->x(),2)+pow(this->y()-scene->fishList.at(i)->y(),2))<distance){
            distance=sqrt(pow(this->x()-scene->fishList.at(i)->x(),2)+pow(this->y()-scene->fishList.at(i)->y(),2));
            nearestFishIndex=i;
        }
    }
    if(nearestFishIndex==-1){
        return;
    }
    if(distance<speed){
        this->move(scene->fishList.at(nearestFishIndex)->x(),scene->fishList.at(nearestFishIndex)->y());
    }else{
        this->move(this->x()+(speed+0.00001)/(distance+0.00001)*(scene->fishList.at(nearestFishIndex)->x()-this->x()),this->y()+(speed+0.00001)/(distance+0.00001)*(scene->fishList.at(nearestFishIndex)->y()-this->y()));
    }
}

void ZBalrog::eatFood(){

}

void ZBalrog::hitten(){
    HP--;
}
