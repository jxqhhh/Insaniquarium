#ifndef ZFOOD_H
#define ZFOOD_H

#include "zobject.h"
#include "gamewidget.h"

class ZFood:public ZObject
{
    Q_OBJECT

public:
    ZFood(ZObject* parent,GameWidget* widget);
    virtual ~ZFood();
    void shift() override;
    void eaten();
protected:
    int energy=1;
};

class pizza:public ZFood{
public:
    pizza(ZObject* parent,GameWidget* widget,int x_init,int y_init);
    ~pizza();
};

class nourishmentPill:public ZFood{
public:
    nourishmentPill(ZObject* parent,GameWidget* widget,int x_init,int y_init);
    ~nourishmentPill();
};

#endif // ZFOOD_H
