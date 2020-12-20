#include "careTaker.h"

careTaker::careTaker(field* f, player* p){
    fM = nullptr;
    pM = nullptr;
    this->fdPtr = f;
    this->plPtr = p;
    playerSave = "playerSave.txt";
    fieldSave = "fieldSave.txt";
    playerSaveFile.open(playerSave, std::ios_base::out);
    fieldSaveFile.open(fieldSave, std::ios_base::out);
}

void careTaker::backup(){
    if(fM){
        delete dynamic_cast<fieldMemento*>(fM);
        fM = nullptr;
    }
    fM = fdPtr->makeSnapshot();
    if(pM){
        delete dynamic_cast<playerMemento*>(pM);
        pM = nullptr;
    }
    pM = plPtr->makeSnapshot();
    fieldSaveFile << fM->getHeight() << '\n' << fM->getWidth() << '\n';
    char** p = fM->getField();
    for(int i = 0; i < fM->getHeight(); i++){
        for(int j = 0; j <  fM->getWidth(); j++){
            fieldSaveFile << p[i][j];
        }
        fieldSaveFile << '\n';
    }
    playerSaveFile << pM->getHp() << '\n' << pM->getGold() << '\n' << pM->getY() << '\n' << pM->getX();
}

void careTaker::undo() {
    fdPtr->restore(fM, *plPtr);
    plPtr->restore(pM);
}

careTaker::~careTaker(){
    playerSaveFile.close();
    fieldSaveFile.close();
}
