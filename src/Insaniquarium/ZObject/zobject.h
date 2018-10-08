#ifndef ZOBJECT_H
#define ZOBJECT_H

class ZScene;
#include <QMovie>
#include <QLabel>
#include "gamewidget.h"
class GameWidget;

class ZObject:public QLabel{
    Q_OBJECT
public:
    ZObject(ZObject* parent,GameWidget* widget);
    virtual ~ZObject();
    virtual void shift();
    bool isAlive() const;
protected:
    bool alive=true;
    ZObject* parent;
};

#endif // ZOBJECT_H
