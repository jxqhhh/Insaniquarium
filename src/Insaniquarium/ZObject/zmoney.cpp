#include "zmoney.h"
#include "zscene.h"

ZMoney::ZMoney(ZObject* parent,GameWidget* widget):ZObject(parent,widget){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    scene->moneyList.append(this);
    connect(this,SIGNAL(money_collected_by_pet(int)),scene,SIGNAL(moneyCollected(int)));
}

ZMoney::~ZMoney()
{

}

void ZMoney::shift(){
    if(this->y()<585){
        this->move(this->x(),this->y()+rand()%2);
    }else{
        alive=false;
    }
    collected_by_pet();
}

void ZMoney::collected_by_pet(){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    for(int i=0;i<scene->petList.count();i++){
        if(dynamic_cast<ZSnail*>(scene->petList[i])!= NULL){
            int dist=sqrt(pow(this->x()-scene->petList[i]->x(),2)+pow(this->y()-scene->petList[i]->y(),2));
            if(dist<50){
                emit(money_collected_by_pet(this->collected()));
            }
        }
    }
}

SilverCoin::SilverCoin(ZObject *parent, GameWidget *widget,int x_init,int y_init):ZMoney(parent,widget){
    this->setGeometry(x_init,y_init,72,72);
    QPixmap pix=QPixmap(":/image/image/SilverCoin.png");
    this->setPixmap(pix);
    this->show();
}

int SilverCoin::collected(){
    if(!alive){
        return 0;
    }
    alive=false;
    return 15;
}

GoldenCoin::GoldenCoin(ZObject *parent, GameWidget *widget, int x_init, int y_init):ZMoney(parent,widget){
    this->setGeometry(x_init,y_init,72,72);
    QPixmap pix=QPixmap(":/image/image/GoldenCoin.png");
    this->setPixmap(pix);
    this->show();
}

int GoldenCoin::collected(){
    if(!alive){
        return 0;
    }
    this->alive=false;
    return 35;
}

Diamond::Diamond(ZObject *parent, GameWidget *widget, int x_init, int y_init):ZMoney(parent,widget){
    this->setGeometry(x_init,y_init,72,72);
    QPixmap pix=QPixmap(":/image/image/Diamond.png");
    this->setPixmap(pix);
    this->show();
}

int Diamond::collected(){
    if(!alive){
        return 0;
    }
    this->alive=false;
    return 200;
}

JewelBox::JewelBox(ZObject *parent, GameWidget *widget, int x_init, int y_init):ZMoney(parent,widget){
    this->setGeometry(x_init,y_init,72,72);
    QPixmap pix=QPixmap(":/image/image/jewelBox.png");
    this->setPixmap(pix);
    this->show();
}

int JewelBox::collected(){
    if(!alive){
        return 0;
    }
    this->alive=false;
    return 2000;
}
