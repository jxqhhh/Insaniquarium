#ifndef ZALIEN_H
#define ZALIEN_H

#include "zobject.h"
#include "gamewidget.h"

class ZAlien:public ZObject{
    Q_OBJECT
public:
    ZAlien(ZObject* parent,GameWidget* widget);
    virtual ~ZAlien();
    virtual void eatFood()=0;//由食物和鱼类的eaten()函数调用
    virtual void shift() override;
    void hitten(bool,bool);
protected:
    int HP;
};

class ZDarkBlueMonster:public ZAlien{
public:
    ZDarkBlueMonster(ZObject *parent, GameWidget *widget);
    void shift() override;
    void eatFood() override;
    int speed=6;
};

class ZGluttonousMonster:public ZAlien{
public:
    ZGluttonousMonster(ZObject* parent,GameWidget* widget);
    void shift() override;
    void eatFood() override;
    int speed=6;
};

class ZBalrog:public ZAlien{
public:
    ZBalrog(ZObject* parent,GameWidget* widget);
    void shift() override;
    void eatFood() override;
    void hitten();
    int speed=6;
};
#endif // ZALIEN_H
