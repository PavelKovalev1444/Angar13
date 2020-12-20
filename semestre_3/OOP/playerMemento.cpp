#include "playerMemento.h"

playerMemento::playerMemento(player& pl){
    this->x = pl.getX();
    this->y = pl.getY();
    this->hp = pl.health;
    this->gold = pl.goldCounter;
}

int playerMemento::getHp(){
    return hp;
}

int playerMemento::getGold() {
    return gold;
}

int playerMemento::getX() {
    return x;
}

int playerMemento::getY(){
    return y;
}
int playerMemento::getHeight(){
    return 1;
}
int playerMemento::getWidth() {
    return 1;
}
char** playerMemento::getField(){
    return nullptr;
}
