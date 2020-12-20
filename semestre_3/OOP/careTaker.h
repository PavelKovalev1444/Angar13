#ifndef CARETAKER_H
#define CARETAKER_H

#include "field.h"
#include "player.h"
#include "memento.h"
#include <ctime>
#include <string>
#include <vector>
#include <fstream>

class careTaker{
    field* fdPtr;
    player* plPtr;
    memento* fM;
    memento* pM;
    std::string playerSave;
    std::string fieldSave;
    std::ofstream playerSaveFile;
    std::ofstream fieldSaveFile;
public:
    careTaker(field* f, player* p);
    void backup();
    void undo();
    ~careTaker();
};

#endif // CARETAKER_H
