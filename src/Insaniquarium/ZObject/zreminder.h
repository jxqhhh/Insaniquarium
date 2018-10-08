#ifndef ZREMINDER_H
#define ZREMINDER_H

#include "zobject.h"
#include "gamewidget.h"

class ZReminder:public ZObject
{
    Q_OBJECT
public:
    ZReminder(ZObject* parent,GameWidget* widget);
    virtual ~ZReminder();

    int HP=400;//在HP次shift()后死亡
};

class ZNewDarkBlueMonsterReminder:public ZReminder{
public:
    ZNewDarkBlueMonsterReminder(ZObject* parent,GameWidget* widget);
    void shift() override;
};

class ZNewGluttonousMonsterReminder:public ZReminder{
public:
    ZNewGluttonousMonsterReminder(ZObject* parent,GameWidget* widget);
    void shift() override;
};

class ZNewBalrogReminder:public ZReminder{
public:
    ZNewBalrogReminder(ZObject* parent,GameWidget* widget);
    void shift() override;
};
#endif // ZREMINDER_H
