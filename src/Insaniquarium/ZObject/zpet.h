#ifndef ZPET_H
#define ZPET_H

#include "zobject.h"
#include "gamewidget.h"

class ZPet:public ZObject{
    Q_OBJECT
public:
    ZPet(ZObject* parent,GameWidget* widget);
    virtual ~ZPet();
    void shift() override;
};

class ZSnail:public ZPet{
    int speed=1;
public:
    ZSnail(ZObject* parent,GameWidget* widget);
    void shift() override;
};

class ZOyster:public ZPet{
    int epoch_before_new_pearl=0;
    bool pearlAvailable=false;
    bool pearlTakenAway=false;
public:
    ZOyster(ZObject* parent,GameWidget* widget);
    void shift() override;
    bool isPearlAvailable() const;
    void pearlCollected();
};

class ZItchy:public ZPet{
    int speed=10;
    int angle=0;
    int num_interval=0;
public:
    ZItchy(ZObject* parent,GameWidget* widget);
    void shift() override;
    void go_to_move();
};
#endif // ZPET_H
