#ifndef ZSCENE_H
#define ZSCENE_H

#include <QList>
#include <QTimer>


#include "zobject.h"
#include "zalien.h"
#include "zfish.h"
#include "zpet.h"
#include "zfood.h"
#include "gamewidget.h"
#include "zmoney.h"
#include "zreminder.h"

class ZObject;
class ZScene:public ZObject{
    Q_OBJECT
public:
    ZScene(ZObject* parent,GameWidget* widget);
    bool judge() const;//判断当前回合是否胜利
    virtual ~ZScene();
    virtual void shift();
    int max_num_of_food=1;//当前ZScene中最多允许的饲料份数
    int currentFoodLevel=1;//当前饲料的等级（等级越高的饲料energy越高）
    const static int foodLevel1=1;
    const static int foodLevel2=2;
    const static int level1=1;//当前的游戏关卡（不是foodLevel）
    const static int level2=2;//当前的游戏关卡（不是foodLevel）
    const static int level3=3;//当前的游戏关卡（不是foodLevel）
    const static int level4=4;
    void removeAll();//清空以准备新的关卡
    void upgrade_food();
    int num_epoch=0;
protected:
    virtual void createAlien()=0;//在派生类ZLevel1、ZLevel2等中重载，每一关alien的出现频率和种类有区别，故可以重载
    void judge();
    int currentLevel=level1;
    bool isStoppingTimerService=false;
private:
    void removeDeath();//移除各个QList中死亡的对象
    QList<ZFish*> fishList;
    QList<ZAlien*> alienList;
    QList<ZPet*> petList;
    QList<ZFood*> foodList;
    QList<ZMoney*> moneyList;
    QList<ZReminder*> reminderList;
    QTimer* myTimer;
    GameWidget* widget;
protected:
    int timerInterval=10;//myTimer的计时频率(ms)
    int seconds_every_alien;//平均多少秒出现一次外星人
public slots:
    void doTimerService();
    void processMousePressed(int x_pos,int y_pos);
    friend class ZAlien;
    friend class ZFish;
    friend class ZFood;
    friend class ZPet;
    friend class ZGuppy;
    friend class ZGuppyMom;
    friend class ZSmallCarnivorousFish;
    friend class ZLargeCarnivorousFish;
    friend class ZMoney;
    friend class ZSnail;
    friend class ZItchy;
    friend class ZBalrog;
    friend class ZDarkBlueMonster;
    friend class ZReminder;
    friend class ZNewDarkBlueMonsterReminder;
    friend class ZGluttonousMonster;
    friend class ZNewGluttonousMonsterReminder;
    friend class ZNewBalrogReminder;
signals:
    void moneyCollected(int money);
};

class ZLevel1:public ZScene{
public:
    ZLevel1(ZObject* parent,GameWidget* widget);
protected:
    void createAlien();
};

#endif // ZSCENE_H
