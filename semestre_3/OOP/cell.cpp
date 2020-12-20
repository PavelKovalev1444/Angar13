#include "cell.h"

cell::cell(){
    isPlayer = false;
    isEnemy = false;
    passability = true;
    entrance = false;
    exit = false;
}

bool cell::get_passability() {
    return passability;
}

bool cell::get_entrance(){
    return entrance;
}

bool cell::get_exit(){
    return exit;
}

void cell::setEntrance(){
    entrance = true;
}

void cell::setExit(){
    exit = true;
}

void cell::set_passability(bool value) {
    passability = value;
}

void cell::setPointer(){
    int a = rand()%20;
    if(a == 1){
        this->pointer = new heal();
    }else if (a == 3){
        this->pointer = new coin();
    }else if (a == 5){
        this->pointer = new bomb();
    }
}

void cell::setIsUsed(){
    isUsed = true;
}

bool cell::getIsUsed(){
    return isUsed;
}

Element* cell::getElemPointer(){
    return this->pointer;
}

void cell::setEnemyPointer(IEnemy* el){
    this->enemyPointer = el;
}

IEnemy* cell::getEnemyPointer() {
    return this->enemyPointer;
}

void cell::setIsPlayer(bool arg){
    this->isPlayer = arg;
}

void cell::setIsEnemy(bool arg){
    this->isEnemy = arg;
}

void cell::setHeal(){
    this->pointer = new heal();
}

void cell::setBomb(){
    this->pointer = new bomb();
}

void cell::setGold(){
    this->pointer = new coin();
}

bool cell::getIsPlayer(){
    return this->isPlayer;
}

bool cell::getIsEnemy(){
    return this->isEnemy;
}

