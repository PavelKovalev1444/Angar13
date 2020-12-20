#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include "cell.h"
#include "standBehaviour.h"
#include "sequreBehaviour.h"
#include "movingBehaviour.h"
#include "Enemy.h"
#include "fieldMemento.h"

class player;

class field{
    int height;
    int width;
    cell** tmp;
    static field* unique;
    field();
public:
    void createField(int h , int w);
    ~field();
    void labirintium();
    int getWidth();
    int getHeight();
    cell** getPointer();
    static field* getInstance();
    void fill();
    void enemyFill(player& pl);
    memento* makeSnapshot();
    void restore(memento* sp, player& pl);
    void restoreFromFile(int h, int w, char** area, player& pl);
    //friend std::ostream& operator<< (std::ostream &out, field & obj);
};

#endif // FIELD_H
