#ifndef PLAYERMEMENTO_H
#define PLAYERMEMENTO_H

#include "memento.h"
#include "player.h"

class playerMemento:public memento{
    int x;
    int y;
    int hp;
    int gold;
public:
    playerMemento(player& pl);
    int getHp() override;
    int getGold() override;
    int getX() override;
    int getY() override;
    int getHeight() override;
    int getWidth() override;
    char** getField() override;
};

#endif // PLAYERMEMENTO_H
