#ifndef CELL_H
#define CELL_H

#include "Element.h"
#include "heal.h"
#include "coin.h"
#include "bomb.h"
#include <ctime>
#include <cstdlib>
#include "IEnemy.h"


class cell{
    bool isPlayer;
    bool isEnemy;
    bool passability;
    bool entrance;
    bool exit;
    Element* pointer = nullptr;
    bool isUsed = false;
    IEnemy* enemyPointer = nullptr;
public:
    cell();
    bool get_passability();
    void set_passability(bool value);
    void setEntrance();
    void setExit();
    bool get_entrance();
    bool get_exit();
    void setPointer();
    void setIsUsed();
    bool getIsUsed();
    void setEnemyPointer(IEnemy* el);
    Element* getElemPointer();
    IEnemy* getEnemyPointer();
    void setIsPlayer(bool arg);
    void setIsEnemy(bool arg);
    void setHeal();
    void setBomb();
    void setGold();
    bool getIsPlayer();
    bool getIsEnemy();
};

#endif // CELL_H
