#include "fieldMemento.h"

fieldMemento::fieldMemento(field* f){
    this->height = f->getHeight();
    this->width = f->getWidth();
    this->charField = new char*[height];
    for(int i = 0; i < height; i++){
        charField[i] = new char[width];
    }
    cell** tmp = f->getPointer();
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(tmp[i][j].getIsPlayer()){
                charField[i][j] = '*';
            }else if(tmp[i][j].get_exit()){
                charField[i][j] = '<';
            }else if(tmp[i][j].get_entrance()) {
                charField[i][j] = '>';
            }else if (tmp[i][j].getIsEnemy()){
                charField[i][j] = 'V';
            }else if (!tmp[i][j].get_passability()){
                charField[i][j] = '#';
            }else if(tmp[i][j].getElemPointer() && !tmp[i][j].getIsUsed()){
                if (tmp[i][j].getElemPointer()->isElem() == 1) {
                    charField[i][j] = 'H';
                } else if (tmp[i][j].getElemPointer()->isElem() == 2) {
                    charField[i][j] = 'G';
                } else if (tmp[i][j].getElemPointer()->isElem() == 3) {
                    charField[i][j] = 'B';
                }
            }else if (tmp[i][j].get_passability()){
                charField[i][j] = '+';
            }
        }
    }
}

int fieldMemento::getHeight(){
    return height;
}

int fieldMemento::getWidth() {
    return width;
}

char** fieldMemento::getField() {
    return charField;
}

int fieldMemento::getHp() {
    return 1;
}

int fieldMemento::getGold(){
    return 1;
}

int fieldMemento::getX() {
    return 1;
}

int fieldMemento::getY() {
    return 1;
}
