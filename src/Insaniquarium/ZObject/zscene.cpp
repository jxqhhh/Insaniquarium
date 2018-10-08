#include "zscene.h"
#include "gamefaileddialog.h"
#include <QApplication>
#include "hintdialog_for_level2.h"
#include "hintdialog_for_level3.h"
#include "hintdialog_for_level4.h"
#include "hintdialogforwin.h"
#include <QDialog>

ZScene::ZScene(ZObject* parent,GameWidget* widget):ZObject(parent,widget),widget(widget){
    myTimer=new QTimer(this);
    myTimer->setInterval(timerInterval);
    myTimer->start();
    connect(myTimer,SIGNAL(timeout()),this,SLOT(doTimerService()));
    currentLevel=level1;
    ZFish* guppy1=new ZGuppy(this,this->widget,50,50);
    ZFish* guppy2=new ZGuppy(this,this->widget,300,300);
}

ZScene::~ZScene()
{

}

void ZScene::doTimerService(){
    if(!isStoppingTimerService){
        this->judge();
        this->shift();
        if(currentLevel==level2){
            num_epoch++;
            num_epoch=num_epoch%6000;
            if(num_epoch==0){
                new ZNewDarkBlueMonsterReminder(this,this->widget);
            }
        }else if(currentLevel==level3){
            num_epoch++;
            num_epoch=num_epoch%9000;
            if(num_epoch==0){
                new ZNewGluttonousMonsterReminder(this,this->widget);
            }else if(num_epoch==4500){
                new ZNewDarkBlueMonsterReminder(this,this->widget);
            }
        }else if(currentLevel==level4){
            num_epoch++;
            num_epoch=num_epoch%9900;
            if(num_epoch==0){
                new ZNewGluttonousMonsterReminder(this,this->widget);
            }else if(num_epoch==3300){
                new ZNewDarkBlueMonsterReminder(this,this->widget);
            }else if(num_epoch==6600){
                new ZNewBalrogReminder(this,this->widget);
            }
        }
    }
}

void ZScene::judge(){
    if(isStoppingTimerService){
        return;
    }
    if(fishList.count()==0){
        GameFailedDialog* dlg=new GameFailedDialog(this);
        int rec=dlg->exec();
        QCoreApplication::quit();
    }
}

void ZScene::removeAll(){
    isStoppingTimerService=true;
    int p=0;
    while (p < fishList.count()){
        delete (fishList[p]);
        fishList.removeAt(p);
    }
    while (p < alienList.count()){
        delete (alienList[p]);
        alienList.removeAt(p);
    }
    while (p < petList.count()){
        delete (petList[p]);
        petList.removeAt(p);
    }
    while (p < foodList.count()){
        delete (foodList[p]);
        foodList.removeAt(p);
    }
    while (p < moneyList.count()){
        delete (moneyList[p]);
        moneyList.removeAt(p);
    }
    currentLevel++;
    currentFoodLevel=foodLevel1;
    max_num_of_food=1;
    if(currentLevel==level2){
        HintDialog_For_Level2 * dlg=new HintDialog_For_Level2(this->widget);
        dlg->exec();
        ZFish* guppy1=new ZGuppy(this,this->widget,50,50);
        ZFish* guppy2=new ZGuppy(this,this->widget,300,300);
        ZSnail* snail=new ZSnail(this,this->widget);
    }else if(currentLevel==level3){
        HintDialog_For_Level3* dlg=new HintDialog_For_Level3(this->widget);
        dlg->exec();
        ZFish* guppy1=new ZGuppy(this,this->widget,50,50);
        ZFish* guppy2=new ZGuppy(this,this->widget,300,300);
        ZSnail* snail=new ZSnail(this,this->widget);
        ZOyster* oyster=new ZOyster(this,this->widget);
    }else if(currentLevel==level4){
        HintDialog_For_Level4* dlg=new HintDialog_For_Level4(this->widget);
        dlg->exec();
        ZFish* guppy1=new ZGuppy(this,this->widget,50,50);
        ZFish* guppy2=new ZGuppy(this,this->widget,300,300);
        ZSnail* snail=new ZSnail(this,this->widget);
        ZOyster* oyster=new ZOyster(this,this->widget);
        new ZItchy(this,this->widget);
    }else{
        HintDialogForWin* dlg=new HintDialogForWin(this->widget);
        dlg->exec();
        QCoreApplication::quit();
    }
    num_epoch=0;
    isStoppingTimerService=false;
}

void ZScene::upgrade_food(){
    if(currentFoodLevel==foodLevel1){
        currentFoodLevel=foodLevel2;
        max_num_of_food=1;
        return;
    }
    if(currentFoodLevel==foodLevel2 && max_num_of_food <=6 ){
        max_num_of_food++;
    }

}

void ZScene::removeDeath(){
    int p=0;
    while (p < fishList.count()){
        if (!(fishList[p]->isAlive())){
            delete (fishList[p]);
            fishList.removeAt(p);
        }
        else{
            p++;
        }
    }
    p=0;
    while (p < alienList.count()){
        if (!(alienList[p]->isAlive())){
            delete (alienList[p]);
            alienList.removeAt(p);
        }
        else{
            p++;
        }
    }
    p=0;
    while (p < petList.count()){
        if (!(petList[p]->isAlive())){
            delete (petList[p]);
            petList.removeAt(p);
        }
        else{
            p++;
        }
    }
    p=0;
    while (p < foodList.count()){
        if (!(foodList[p]->isAlive())){
            delete (foodList[p]);
            foodList.removeAt(p);
        }
        else{
            p++;
        }
    }
    p=0;
    while (p < moneyList.count()){
        if (!(moneyList[p]->isAlive())){
            delete (moneyList[p]);
            moneyList.removeAt(p);
        }
        else{
            p++;
        }
    }
    p=0;
    while (p < reminderList.count()){
        if (!(reminderList[p]->isAlive())){
            delete (reminderList[p]);
            reminderList.removeAt(p);
        }
        else{
            p++;
        }
    }
}

void ZScene::processMousePressed(int x_pos, int y_pos){
    if(currentLevel>level2 && x_pos>=165 && x_pos<=245 && y_pos>=370 && y_pos<=450){//先判断是否是在取Oyster的pearl
        for(int i=0;i!=petList.size();i++){
            ZOyster* niko=dynamic_cast<ZOyster*>(petList[i]);
            if(niko!=NULL){
                if(niko->isPearlAvailable()){
                    niko->pearlCollected();
                    emit(moneyCollected(250));
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i!=alienList.size();i++){
        ZAlien* monster=alienList[i];
        int x=alienList.at(i)->x();
        int y=alienList.at(i)->y();
        int w=alienList.at(i)->width();
        int h=alienList.at(i)->height();
        if(x_pos>=x && x_pos<=x+w && y_pos>=y && y_pos<=y+h){
            if(x_pos<=x+0.5*w){
                if(y_pos<=y+0.5*h){
                    monster->hitten(true,true);
                }else{
                    monster->hitten(true,false);
                }
            }else{
                if(y_pos<=y+0.5*h){
                    monster->hitten(false,true);
                }else{
                    monster->hitten(false,false);
                }
            }
            return;
        }
    }
    for(int i=0;i!=moneyList.size();i++){
        int x=moneyList.at(i)->x();
        int y=moneyList.at(i)->y();
        int w=moneyList.at(i)->width();
        int h=moneyList.at(i)->height();
        if(x_pos>=x && x_pos<=x+w && y_pos>=y && y_pos<=y+h){
            if(!moneyList.at(i)->isAlive()){
                continue;
            }
            emit(moneyCollected(moneyList[i]->collected()));
            return;
        }
    }

        int num=foodList.size();
        if(num<max_num_of_food){
            if(currentFoodLevel==foodLevel1){
                pizza* my_pizza=new pizza(this,this->widget,x_pos,y_pos);
            }else if(currentFoodLevel==foodLevel2){
                nourishmentPill* pill=new nourishmentPill(this,this->widget,x_pos,y_pos);
            }
        }

}

void ZScene::shift(){
    this->removeDeath();
    for(int i=0;i!=foodList.size();i++){
        foodList[i]->shift();
    }
    for(int i=0;i!=fishList.size();i++){
        fishList[i]->shift();
    }   
    for(int i=0;i!=alienList.size();i++){
        alienList[i]->shift();
    }
    for(int i=0;i!=petList.size();i++){
        petList[i]->shift();
    }
    for(int i=0;i!=moneyList.size();i++){
        moneyList[i]->shift();
    }
    for(int i=0;i!=reminderList.size();i++){
        reminderList[i]->shift();
    }
}

ZLevel1::ZLevel1(ZObject* parent,GameWidget* widget):ZScene(parent,widget){
    seconds_every_alien=180;
}

void ZLevel1::createAlien(){

}
