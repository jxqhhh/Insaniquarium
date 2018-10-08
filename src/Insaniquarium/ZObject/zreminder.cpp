#include "zreminder.h"
#include "zscene.h"
#include <QFont>

ZReminder::ZReminder(ZObject *parent, GameWidget *widget):ZObject(parent,widget){
    ZScene* scene=dynamic_cast<ZScene*>(this->parent);
    scene->reminderList.append(this);
}

ZReminder::~ZReminder()
{

}

ZNewDarkBlueMonsterReminder::ZNewDarkBlueMonsterReminder(ZObject *parent, GameWidget *widget):ZReminder(parent,widget){
    this->setGeometry(QRect(150, 585, 695, 51));
    QFont font;
    font.setPointSize(20);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);
    this->setText(QString::fromStdString("DARK BLUE MONSTER APPROACHING"));
    this->show();
}

void ZNewDarkBlueMonsterReminder::shift(){
    HP--;
    if(HP==0){
        ZScene* scene=dynamic_cast<ZScene*>(this->parent);
        alive=false;
        new ZDarkBlueMonster(this->parent,scene->widget);
    }
}

ZNewGluttonousMonsterReminder::ZNewGluttonousMonsterReminder(ZObject *parent, GameWidget *widget):ZReminder(parent,widget){
    this->setGeometry(QRect(150, 585, 695, 51));
    QFont font;
    font.setPointSize(20);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);
    this->setText(QString::fromStdString("GLUTTONOUS MONSTER APPROACHING"));
    this->show();
}

void ZNewGluttonousMonsterReminder::shift(){
    HP--;
    if(HP==0){
        ZScene* scene=dynamic_cast<ZScene*>(this->parent);
        alive=false;
        new ZGluttonousMonster(this->parent,scene->widget);
    }
}

ZNewBalrogReminder::ZNewBalrogReminder(ZObject *parent, GameWidget *widget):ZReminder(parent,widget){
    this->setGeometry(QRect(150, 585, 695, 51));
    QFont font;
    font.setPointSize(20);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);
    this->setText(QString::fromStdString("BALROG APPROACHING"));
    this->show();
}


void ZNewBalrogReminder::shift(){
    HP--;
    if(HP==0){
        ZScene* scene=dynamic_cast<ZScene*>(this->parent);
        alive=false;
        new ZBalrog(this->parent,scene->widget);
    }
}
