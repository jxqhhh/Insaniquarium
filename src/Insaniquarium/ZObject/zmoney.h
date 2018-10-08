#ifndef ZMONEY_H
#define ZMONEY_H

#include "zobject.h"
#include "gamewidget.h"

class ZMoney:public ZObject
{
    Q_OBJECT

public:
    ZMoney(ZObject* parent,GameWidget* widget);
    virtual ~ZMoney();
    void shift() override;
    virtual int collected()=0;
private:
    void collected_by_pet();
signals:
    void money_collected_by_pet(int money);
};


class SilverCoin:public ZMoney{
public:
    SilverCoin(ZObject* parent,GameWidget* widget,int x_init,int y_init);
    int collected() override;
};

class GoldenCoin:public ZMoney{
public:
    GoldenCoin(ZObject* parent,GameWidget* widget,int x_init,int y_init);
    int collected() override;
};

class Diamond:public ZMoney{
public:
    Diamond(ZObject* parent,GameWidget* widget,int x_init,int y_init);
    int collected() override;
};

class JewelBox:public ZMoney{
public:
    JewelBox(ZObject* parent,GameWidget* widget,int x_init,int y_init);
    int collected() override;
};

#endif // ZMONEY_H
