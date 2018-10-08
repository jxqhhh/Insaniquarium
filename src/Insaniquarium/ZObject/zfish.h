#ifndef ZFISH_H
#define ZFISH_H

#include "zobject.h"
#include "gamewidget.h"

class ZFish:public ZObject
{
    Q_OBJECT
public:
    ZFish(ZObject* parent,GameWidget* widget);
    virtual ~ZFish();
    virtual void eaten();//判断周围有没有可以吃它的，如果有就把它吃了（适用于鱼被鱼吃、鱼被怪物吃）
    int get_X() const;//返回当前该鱼的x坐标，每个食物都会选择最近的鱼让它来吃饲料，计算食物和鱼的距离时会调用此处的get_X()函数
    int get_Y() const;
    bool is_fed_on_fodder() const;

    int angle=0;
    int speed=5;
    void shift();
    int num_interval=0;
    int epoch_before_produce=0;
    virtual void eatFood(int food_energy);
    void eatenByMonster();
    bool isGoingToEat=false;
    bool hungry() const;
protected:
    bool fed_on_fodder=false;//存储这种鱼是否吃饲料，如食肉鱼的构造函数中应将此项设为false
    int hungerValue=0;//每过一段时间都会增加，当增加到等于max_HungerValue时死亡
    bool isHungry=false;
    virtual void go_to_eat()=0;
    virtual void go_to_move()=0;
    virtual void update_state()=0;//更新状态，包括是否饥饿，是否死亡
    virtual bool isFoodAvailable()=0;//判断是否有食物
    virtual void produce()=0;//古比鱼产生货币，古比妈咪产生古比‘
    int currentPixmapIndex=0;
};

class ZGuppy:public ZFish{
    int energy=0;//能量值，随着能量值的增大，小古比鱼会逐渐发育成大古比鱼
    int currentState;//记录当前是小古比鱼、中古比鱼、大古比鱼还是古比鱼王
    const static int SmallGuppy=0;
    const static int MidGuppy=1;
    const static int LargeGuppy=2;
    const static int GuppyKing=3;
    const static int min_energy_for_MidGuppy=2;
    const static int min_energy_for_LargeGuppy=4;
    const static int min_HungerValue=3000;
    const static int max_HungerValue=6000;
    const static int frequency_for_produce=2000;
public:
    ZGuppy(ZObject* parent,GameWidget* widget,int x_init,int y_init);
    void go_to_eat() override;
    bool isFoodAvailable() override;
    void update_state() override;
    void eatFood(int food_energy) override;
    void produce() override;
    bool isSmallGuppy();
    void go_to_move() override;
    void eaten() override;
};

class ZGuppyMom:public ZFish{
    int energy=0;
    const static int min_energy_for_LargeGuppyMom=4;
    const static int min_HungerValue=3000;
    const static int max_HungerValue=6000;
    const static int SmallGuppyMom=0;
    const static int LargeGuppyMom=1;
    const static int frequency_for_SmallGuppyMom_produce=3000;
    const static int frequency_for_LargeGuppyMom_produce=1500;
    int currentState;//记录当前是小古比鱼妈咪还是大古比鱼妈咪
public:
    ZGuppyMom(ZObject* parent,GameWidget* widget,int x_init,int y_init);
    void go_to_eat() override;
    bool isFoodAvailable() override;
    void update_state() override;
    void produce() override;
    void eatFood(int food_energy) override;
    void go_to_move() override;
};

class ZSmallCarnivorousFish:public ZFish{
public:
    ZSmallCarnivorousFish(ZObject* parent,GameWidget* widget);
    void go_to_eat() override;
    bool isFoodAvailable() override;
    void update_state() override;
    void produce() override;
    const static int min_HungerValue=4000;
    const static int max_HungerValue=7000;
    void go_to_move() override;
    void eatFood();
    const static int frequency_for_produce=3000;
    void eaten() override;
private:
    int currentPixmapIndex=0;
};

class ZLargeCarnivorousFish:public ZFish{
public:
    ZLargeCarnivorousFish(ZObject* parent,GameWidget* widget);
    void go_to_eat() override;
    bool isFoodAvailable() override;
    void update_state() override;
    void produce() override;
    const static int min_HungerValue=4000;
    const static int max_HungerValue=7000;
    void go_to_move() override;
    void eatFood();
    const static int frequency_for_produce=3000;
private:
    int currentPixmapIndex=0;
};
#endif // ZFISH_H
