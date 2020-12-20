#ifndef PLAYER_H
#define PLAYER_H

#include "field.h"
#include "cell.h"
#include "playerMemento.h"
class field;

class player{
    player();
static player* unique;
public:
    int health = 100;
    int goldCounter = 0;
    field* fieldPtr;
    int x;
    int y;

    static player* getInstance();
    void restoreFromFile(int hp, int gd, int yCoord, int xCoord);
    void addHp(int a, int x, int y);
    void addGold(int x, int y);
    void operator+= (int a);
    field* getPointer();
    int goUp();
    int goDown();
    int goLeft();
    int goRight();
    int getHealth();
    int getGold();
    int getX();
    int getY();
    memento* makeSnapshot();
    void restore(memento* sp);
    friend std::ostream& operator<< (std::ostream &out, player& obj);
};

#endif // PLAYER_H
