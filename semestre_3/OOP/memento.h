#ifndef MEMENTO_H
#define MEMENTO_H

#include <iostream>

class memento{
public:
    virtual int getHeight() = 0;
    virtual int getWidth() = 0;
    virtual char** getField() = 0;
    virtual int getHp() = 0;
    virtual int getGold() = 0;
    virtual int getX() = 0;
    virtual int getY() = 0;
};

#endif // MEMENTO_H
