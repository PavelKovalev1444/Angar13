#include "movingBehaviour.h"

#include "player.h"
#include "IEnemy.h"

void movingBehaviour::behave(field* fieldPtr, player& pl, IEnemy* enemy, int& xNow, int& yNow){
    srand(time(0));
    int choice = rand()%4;
    if(choice == 0){
        if(xNow - 1 >= 0){
            if(fieldPtr->getPointer()[yNow][xNow - 1].get_passability()) {
                fieldPtr->getPointer()[yNow][xNow].setIsEnemy(false);
                xNow = xNow - 1;
                fieldPtr->getPointer()[yNow][xNow].setIsEnemy(true);
            }
        }
    }else if (choice == 1){
        if(yNow - 1 >= 0){
            if(fieldPtr->getPointer()[yNow - 1][xNow].get_passability()) {
                fieldPtr->getPointer()[yNow][xNow].setIsEnemy(false);
                yNow = yNow - 1;
                fieldPtr->getPointer()[yNow][xNow].setIsEnemy(true);
            }
        }
    }else if (choice == 2){
        if(xNow + 1 < fieldPtr->getWidth()){
            if(fieldPtr->getPointer()[yNow][xNow+1].get_passability()) {
                fieldPtr->getPointer()[yNow][xNow].setIsEnemy(false);
                xNow = xNow + 1;
                fieldPtr->getPointer()[yNow][xNow].setIsEnemy(true);
            }
        }
    }else if (choice == 3){
        if(yNow + 1 < fieldPtr->getHeight()){
            if(fieldPtr->getPointer()[yNow + 1][xNow].get_passability()) {
                fieldPtr->getPointer()[yNow][xNow].setIsEnemy(false);
                yNow = yNow + 1;
                fieldPtr->getPointer()[yNow][xNow].setIsEnemy(true);
            }
        }
    }
    if(pl.getX() == xNow && pl.getY() == yNow){
        *this += pl;
        return;
    }
    if(pl.getY() == yNow){
        if(pl.getX() == xNow - 1){
            *this += pl;
        }else if(pl.getX() == xNow + 1){
            *this += pl;
        }
    }
    if(pl.getX() == xNow){
        if(pl.getY() == yNow -1){
            *this += pl;
        }else if(pl.getY() == yNow -1){
            *this += pl;
        }
    }
}

void movingBehaviour::operator+= (player& pl){
    pl.health = pl.health - 25;
    if(pl.health < 0){
        pl.health = 0;
    }
}
