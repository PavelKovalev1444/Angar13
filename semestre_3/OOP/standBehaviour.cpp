#include "standBehaviour.h"
#include "player.h"

void standBehaviour::behave(field* fieldPtr, player& pl, IEnemy* enemy, int xNow, int yNow){
    if(pl.getY() == yNow){
        if(pl.getX() == xNow - 2){
            *this += pl;
        }else if(pl.getX() == xNow + 2){
            *this += pl;
        }
        return;
    }
    if(pl.getX() == xNow){
        if(pl.getY() == yNow - 2){
            *this += pl;
        }else if(pl.getY() == yNow - 2){
            *this += pl;
        }
        return;
    }
    if(pl.getY() == yNow){
        if(pl.getX() == xNow - 1){
            *this += pl;
        }else if(pl.getX() == xNow + 1){
            *this += pl;
        }
        return;
    }
    if(pl.getX() == xNow) {
        if (pl.getY() == yNow - 1) {
            *this += pl;
        } else if (pl.getY() == yNow - 1) {
            *this += pl;
        }
        return;
    }
    if(pl.getX() == xNow && pl.getY() == yNow){
        *this += pl;
        return;
    }
}

void standBehaviour::operator+= (player& pl){
    pl.health = pl.health - 50;
    if(pl.health < 0){
        pl.health = 0;
    }
}
