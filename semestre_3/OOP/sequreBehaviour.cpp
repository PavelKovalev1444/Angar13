#include "sequreBehaviour.h"
#include "player.h"

void secureBehaviour::behave(field* fieldPtr, player& pl, IEnemy* enemy, int xNow, int yNow){
    if(pl.getX() == xNow && pl.getY() == yNow){
        *this += pl;
        *this += enemy;
        if(enemy->enemyHp == 0){
            fieldPtr->getPointer()[yNow][xNow].setIsEnemy(false);
        }
        return;
    }
    if(pl.getY() == yNow){
        if(pl.getX() == xNow - 1){
            *this += pl;
            *this += enemy;
        }else if(pl.getX() == xNow + 1){
            *this += pl;
            *this += enemy;
        }
        if(enemy->enemyHp == 0){
            fieldPtr->getPointer()[yNow][xNow].setIsEnemy(false);
        }
    }
    if(pl.getX() == xNow){
        if(pl.getY() == yNow -1){
            *this += pl;
            *this += enemy;
        }else if(pl.getY() == yNow -1){
            *this += pl;
            *this += enemy;
        }
        if(enemy->enemyHp == 0){
            fieldPtr->getPointer()[yNow][xNow].setIsEnemy(false);
        }
    }
}

void secureBehaviour::operator+= (player& pl){
    pl.health = pl.health - 25;
    if(pl.health < 0){
        pl.health = 0;
    }
}

void secureBehaviour::operator+= (IEnemy* enemy){
    enemy->enemyHp = enemy->enemyHp - 50;
}
