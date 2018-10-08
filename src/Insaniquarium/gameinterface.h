#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <QWidget>
#include "ZObject/zscene.h"
#include <QTimer>
#include "gamewidget.h"
namespace Ui {
class GameInterface;
}

class GameInterface : public QWidget
{
    Q_OBJECT

public:
    explicit GameInterface(QWidget *parent = 0);
    ~GameInterface();    
    //当前的游戏关卡：
    const static int level1=1;
    const static int level2=2;
    const static int level3=3;
    const static int level4=4;
    //当前的食物等级
    const static int foodLevel1=1;
    const static int foodLevel2=2;
private:
    Ui::GameInterface *ui;
    ZScene* scene;
    GameWidget* widget;
    int total_money=0;
    int currentEggNum=0;//当前拥有的宠物蛋数量，等于3时通关
    int currentLevel=level1;//当前所处的关卡
    int currentFoodLevel=foodLevel1;
    void startNewLevel(int newLevel);
    void winGame();//游戏获胜
    int max_num_of_food=1;
private slots:
    void moneyCollected(int money);
    void on_buy_new_guppy_clicked();
    void on_upgrade_food_clicked();
    void on_buy_new_guppyMom_clicked();
    void on_buy_egg_clicked();
    void on_num_of_food_clicked();
    void on_buy_small_carnivorous_fish_clicked();
    void on_buy_large_carnivorous_fish_clicked();
};

#endif // GAMEINTERFACE_H
