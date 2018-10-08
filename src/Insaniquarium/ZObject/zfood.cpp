#include "zfood.h"
#include "zscene.h"
#include <QDebug>
#include <climits>
#include <cmath>
#include <string>

ZFood::ZFood(ZObject* parent,GameWidget* widget):ZObject(parent,widget){
    ZScene* scene=dynamic_cast<ZScene*>(parent);
    scene->foodList.append(this);
}

ZFood::~ZFood(){
}

void ZFood::shift(){
    if(this->y()<585){
        this->move(this->x(),this->y()+1);
    }else{
        alive=false;
    }
    eaten();
}

void ZFood::eaten(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    int distance=INT_MAX;
    int nearestGubbyIndex=-1;//包括Gubby和GubbyMom

    for(int i=0;i<scene->fishList.count();i++){
        if(dynamic_cast<ZGuppy*>(scene->fishList[i])!= NULL || dynamic_cast<ZGuppyMom*>(scene->fishList[i])!=NULL){
            int dist=sqrt(pow(this->x()-scene->fishList[i]->x(),2)+pow(this->y()-scene->fishList[i]->y(),2));
            if(dist<distance){
                distance=dist;
                nearestGubbyIndex=i;
            }
        }
    }
    if(nearestGubbyIndex>=0 && distance<=30){
        this->alive=false;
        scene->fishList[nearestGubbyIndex]->eatFood(this->energy);
        return;
    }

    int nearestGluttonousMonsterIndex=-1;
    distance=INT_MAX;
    for(int i=0;i<scene->alienList.count();i++){
        if(dynamic_cast<ZGluttonousMonster*>(scene->alienList[i])!= NULL){
            int dist=sqrt(pow(this->x()-scene->alienList[i]->x(),2)+pow(this->y()-scene->alienList[i]->y(),2));
            if(dist<distance){
                distance=dist;
                nearestGluttonousMonsterIndex=i;
            }
        }
    }
    if(nearestGluttonousMonsterIndex>=0 && distance<=30){
        this->alive=false;
        scene->alienList[nearestGluttonousMonsterIndex]->eatFood();
        return;
    }
}

pizza::pizza(ZObject* parent,GameWidget* widget,int x_init,int y_init):ZFood(parent,widget){
    this->setGeometry(x_init,y_init,40,40);
    QPixmap pix=QPixmap(":/image/image/pizza.png");
    this->setPixmap(pix);
    this->show();
    energy=1;
}

pizza::~pizza(){

}

nourishmentPill::nourishmentPill(ZObject *parent, GameWidget *widget, int x_init, int y_init):ZFood(parent,widget){
    this->setGeometry(x_init,y_init,40,40);
    QPixmap pix=QPixmap(":/image/image/nourishmentPill.png");
    this->setPixmap(pix);
    this->show();
    energy=2;
}

nourishmentPill::~nourishmentPill(){

}
