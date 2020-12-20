#ifndef FIELDMEMENTO_H
#define FIELDMEMENTO_H

#include "memento.h"
#include "field.h"

class fieldMemento:public memento{
    int height;
    int width;
    char** charField;
public:
    fieldMemento(field* f);
    int getHeight() override;
    int getWidth() override;
    char** getField() override;
    int getHp() override;
    int getGold() override;
    int getX() override;
    int getY() override;
};
#endif // FIELDMEMENTO_H
