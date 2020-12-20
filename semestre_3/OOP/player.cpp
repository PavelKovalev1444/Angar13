#include "player.h"

int player::getHealth(){
    return this->health;
}

player* player::getInstance() {
    if(unique == nullptr){
        unique = new player();
    }
    return unique;
}


void player::addHp(int a, int x, int y){
    if((this->health < 100 && a == 25) || a == -25) {
        this->health = this->health + a;
        fieldPtr->getPointer()[y][x].setIsUsed();
    }
}

field* player::getPointer(){
    return fieldPtr;
}

int player::getX(){
    return this->x;
}

int player::getY(){
    return this->y;
}

void player::addGold(int x, int y){
    this->goldCounter += 1;
    fieldPtr->getPointer()[y][x].setIsUsed();
}

player::player(): fieldPtr(field::getInstance()){
    this->x = 0;
    this->y = 0;
    //fieldPtr->getPointer()[0][0].setIsPlayer(true);
}

void player::restoreFromFile(int hp, int gd, int yCoord, int xCoord){
    this->health = hp;
    this->goldCounter = gd;
    this->y = yCoord;
    this->x = xCoord;
}

int player::goUp(){
    if(this->y - 1 >= 0){
        if(field::getInstance()->getPointer()[this->y - 1][this->x].get_passability()){
            field::getInstance()->getPointer()[this->y][this->x].setIsPlayer(false);
            this->y = this->y - 1;
            field::getInstance()->getPointer()[this->y][this->x].setIsPlayer(true);
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int player::goDown(){
    if(this->y + 1 < field::getInstance()->getHeight()){
        if(field::getInstance()->getPointer()[this->y + 1][this->x].get_passability()){
            field::getInstance()->getPointer()[this->y][this->x].setIsPlayer(false);
            this->y = this->y + 1;
            field::getInstance()->getPointer()[this->y][this->x].setIsPlayer(true);
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int player::goLeft(){
    if(this->x - 1 >= 0){
        if(field::getInstance()->getPointer()[this->y][this->x - 1].get_passability()){
            field::getInstance()->getPointer()[this->y][this->x].setIsPlayer(false);
            this->x = this->x - 1;
            field::getInstance()->getPointer()[this->y][this->x].setIsPlayer(true);
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int player::goRight(){
    if(this->x + 1 < field::getInstance()->getWidth()){
        if(field::getInstance()->getPointer()[this->y][this->x + 1].get_passability()){
            field::getInstance()->getPointer()[this->y][this->x].setIsPlayer(false);
            this->x = this->x + 1;
            field::getInstance()->getPointer()[this->y][this->x].setIsPlayer(true);
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

void player::operator+= (int a){
    if(a == 25){
        addHp(a, this->x, this->y);
    }else if (a == -25){
        addHp(a, this->x, this->y);
    }else if (a == 1){
        addGold(this->x, this->y);
    }
}

int player::getGold(){
    return this->goldCounter;
}

memento* player::makeSnapshot() {
    return new playerMemento(*this);
}

void player::restore(memento* sp){
    this->x = sp->getX();
    this->y = sp->getY();
    this->health = sp->getHp();
    this->goldCounter = sp->getGold();
}

std::ostream& operator<< (std::ostream &out, player& obj){
    int h = 0, w = 0, gold = 0, heal = 0, bomb = 0;
    h = obj.getPointer()->getHeight();
    w = obj.getPointer()->getWidth();
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(obj.getPointer()->getPointer()[i][j].getElemPointer()){
                if(obj.getPointer()->getPointer()[i][j].getElemPointer()->isElem() == 1){
                    heal += 1;
                }else if (obj.getPointer()->getPointer()[i][j].getElemPointer()->isElem() == 2){
                    gold += 1;
                }else{
                    bomb += 1;
                }
            }
        }
    }
    out << "Player is on coordinates X = " << obj.getX() << " Y = " << obj.getY() << ". Health is " << obj.getHealth() << " points. " << obj.getGold() << " gold player has. " << heal << " healthbottles are on map. " << gold << " gold ingots are on map. " << bomb << " bombs are on map.\n";
    return out;
}
player* player::unique = nullptr;
