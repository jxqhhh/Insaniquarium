#include "zobject.h"
#include <QDebug>

ZObject::ZObject(ZObject* parent,GameWidget* widget):QLabel(widget),parent(parent){

}

ZObject::~ZObject(){
}

bool ZObject::isAlive() const{
    return alive;
}

void ZObject::shift(){

}
