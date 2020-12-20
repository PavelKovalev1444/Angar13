#include "field.h"

field::field(){
    tmp = nullptr;
    height = 0;
    width = 0;
}

void field::createField(int h , int w){
    this->height = h;
    this->width = w;
    tmp = new cell*[height];
    for(int i = 0; i < height; i++){
        tmp[i] = new cell[width];
    }
    labirintium();
    fill();
    tmp[0][0].setIsPlayer(true);
}

field::~field(){
    for(int i = 0; i < height; i++){
        delete [] tmp[i];
    }
    delete [] tmp;
}

void field::labirintium(){
    srand(time(0));
    tmp[0][0].setEntrance();
    tmp[height - 1][width - 1].setExit();
    for(int i = 1; i < height; i++){
        tmp[i][0].set_passability(false);

    }
    for(int i = 1; i < height; i++){
        for(int j = 1; j < width - 1; j++){
            if(j%2){
                if (rand() % 2) {
                    tmp[i][j].set_passability(true);
                } else {
                    tmp[i][j].set_passability(false);
                }
            }
        }
    }
}

int field::getWidth(){
    return width;
}

int field::getHeight(){
    return height;
}

cell** field::getPointer(){
    return tmp;
}

/*
void field::printer(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(tmp[i][j].getIsPlayer()){
                std::cout << "*" << " ";
            }else if(tmp[i][j].get_exit()){
                std::cout << "<" << " ";
            }else if(tmp[i][j].get_entrance()) {
                std::cout << ">" << " ";
            }else if (tmp[i][j].getIsEnemy()){
                std::cout << "V ";
            }else if (!tmp[i][j].get_passability()){
                std::cout << "#" << " ";
            }else if(tmp[i][j].getElemPointer() && !tmp[i][j].getElemPointer()->isUsed){
                if (tmp[i][j].getElemPointer()->isElem() == 1) {
                    std::cout << "H ";
                } else if (tmp[i][j].getElemPointer()->isElem() == 2) {
                    std::cout << "G ";
                } else if (tmp[i][j].getElemPointer()->isElem() == 3) {
                    std::cout << "B ";
                }
            }else if (tmp[i][j].get_passability()){
                std::cout << "+" << " ";
            }
        }
        std::cout << '\n';
    }
}
*/
field* field::getInstance() {
    if(unique == nullptr){
        unique = new field();
    }
    return unique;
}

void field::fill(){
    srand(time(0));
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            if(tmp[i][j].get_passability() && !tmp[i][j].get_entrance() && !tmp[i][j].get_exit() ){
                tmp[i][j].setPointer();
                tmp[i][j].setIsEnemy(false);
            }
        }
    }
}

void field::enemyFill(player& pl){
    int i = height/2;
    int j = width/2;
    if(tmp[i][j].get_passability()){
        auto* sb = new standBehaviour();
        auto* en = new Enemy<standBehaviour>(sb, i, j, unique, pl);
        tmp[i][j].setEnemyPointer(en);
        tmp[i][j].setIsEnemy(true);
    }else if (tmp[i+1][j].get_passability()){
        auto* sb = new standBehaviour();
        auto* en = new Enemy<standBehaviour>(sb, i+1, j, unique, pl);
        tmp[i+1][j].setEnemyPointer(en);
        tmp[i+1][j].setIsEnemy(true);
    }else if (tmp[i-1][j].get_passability()){
        auto* sb = new standBehaviour();
        auto* en = new Enemy<standBehaviour>(sb, i-1, j, unique, pl);
        tmp[i-1][j].setEnemyPointer(en);
        tmp[i-1][j].setIsEnemy(true);
    }else if (tmp[i][j-1].get_passability()){
        auto* sb = new standBehaviour();
        auto* en = new Enemy<standBehaviour>(sb, i, j-1, unique, pl);
        tmp[i][j-1].setEnemyPointer(en);
        tmp[i][j-1].setIsEnemy(true);
    }else if (tmp[i][j+1].get_passability()){
        auto* sb = new standBehaviour();
        auto* en = new Enemy<standBehaviour>(sb, i, j+1, unique, pl);
        tmp[i][j+1].setEnemyPointer(en);
        tmp[i][j+1].setIsEnemy(true);
    }
    i = height - 1;
    for(j = 0; j < width; j++){
        if(tmp[i][j].get_passability()){
            auto* sb = new movingBehaviour();
            auto* en = new Enemy<movingBehaviour>(sb, i, j, unique, pl);
            tmp[i][j].setEnemyPointer(en);
            tmp[i][j].setIsEnemy(true);
            break;
        }
    }
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            if (tmp[i][j].getElemPointer()){
                if (tmp[i][j].getElemPointer()->isElem() == 2){
                    if (tmp[i+1][j].get_passability()){
                        auto* sb = new secureBehaviour();
                        auto* en = new Enemy<secureBehaviour>(sb, i+1, j, unique, pl);
                        tmp[i+1][j].setEnemyPointer(en);
                        tmp[i+1][j].setIsEnemy(true);
                        break;
                    }else if (tmp[i-1][j].get_passability()){
                        auto* sb = new secureBehaviour();
                        auto* en = new Enemy<secureBehaviour>(sb, i-1, j, unique, pl);
                        tmp[i-1][j].setEnemyPointer(en);
                        tmp[i-1][j].setIsEnemy(true);
                        break;
                    }else if (tmp[i][j-1].get_passability()){
                        auto* sb = new secureBehaviour();
                        auto* en = new Enemy<secureBehaviour>(sb, i, j-1, unique, pl);
                        tmp[i][j-1].setEnemyPointer(en);
                        tmp[i][j-1].setIsEnemy(true);
                        break;
                    }else if (tmp[i][j+1].get_passability()){
                        auto* sb = new secureBehaviour();
                        auto* en = new Enemy<secureBehaviour>(sb, i, j+1, unique, pl);
                        tmp[i][j+1].setEnemyPointer(en);
                        tmp[i][j+1].setIsEnemy(true);
                        break;
                    }
                }
            }
        }
    }
}

memento* field::makeSnapshot(){
    return new fieldMemento(this);
}

void field::restore(memento* sp, player& pl){
    this->height = sp->getHeight();
    this->width = sp->getWidth();
    char** pt = sp->getField();
    for(int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if(tmp[i][j].getIsPlayer()){
                tmp[i][j].setIsPlayer(false);
                break;
            }
        }
    }
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            if(pt[i][j] == '>'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setEntrance();
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == '<'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setExit();
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == '#'){
                tmp[i][j].set_passability(false);
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == '+'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == '*'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setIsPlayer(true);
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == 'H'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setHeal();
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == 'B'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setBomb();
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == 'G'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setGold();
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == 'V') {
                tmp[i][j].set_passability(true);
                srand(time(nullptr));
                int a = rand();
                if(a%3 == 0) {
                    tmp[i][j].setEnemyPointer(new Enemy<standBehaviour>(new standBehaviour(), i, j, unique, pl));
                }else if(a%3 == 1){
                    tmp[i][j].setEnemyPointer(new Enemy<secureBehaviour>(new secureBehaviour(), i, j, unique, pl));
                }else if(a%3 == 2){
                    tmp[i][j].setEnemyPointer(new Enemy<movingBehaviour>(new movingBehaviour(), i, j, unique, pl));

                }
                tmp[i][j].setIsEnemy(true);
            }
        }
    }
}

void field::restoreFromFile(int h, int w, char** area, player& pl){
    this->height = h;
    this->width = w;
    char** pt = area;
    tmp = new cell*[h];
    for(int i = 0; i < height; i++){
        tmp[i] = new cell[width];
    }
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            if(pt[i][j] == '>'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setEntrance();
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == '<'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setExit();
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == '#'){
                tmp[i][j].set_passability(false);
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == '+'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == '*'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setIsPlayer(true);
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == 'H'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setHeal();
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == 'B'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setBomb();
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == 'G'){
                tmp[i][j].set_passability(true);
                tmp[i][j].setGold();
                tmp[i][j].setIsEnemy(false);
            }else if(pt[i][j] == 'V') {
                tmp[i][j].set_passability(true);
                srand(time(nullptr));
                int a = rand();
                if(a%3 == 0) {
                    tmp[i][j].setEnemyPointer(new Enemy<standBehaviour>(new standBehaviour(), i, j, unique, pl));
                }else if(a%3 == 1){
                    tmp[i][j].setEnemyPointer(new Enemy<secureBehaviour>(new secureBehaviour(), i, j, unique, pl));
                }else if(a%3 == 2){
                    tmp[i][j].setEnemyPointer(new Enemy<movingBehaviour>(new movingBehaviour(), i, j, unique, pl));
                }
                tmp[i][j].setIsEnemy(true);
            }
        }
    }
}

/*
std::ostream& operator<< (std::ostream &out, field & obj){
    int h = obj.getHeight();
    int w = obj.getWidth();
    int heal = 0, gold = 0, bomb = 0;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(!obj.getPointer()[i][j].getElemPointer()->isUsed){
                if(obj.getPointer()[i][j].getElemPointer()->isElem() == 1){
                    heal++;
                }else if (obj.getPointer()[i][j].getElemPointer()->isElem() == 2)
                    gold++;
                else{
                    bomb++;
                }
            }
        }
    }
    out << "Healthbottles on map: " << heal << ". GoldIngots on map: " << gold << ". Bombs on map: " << bomb << ".\n";
    return out;
}
*/
field* field::unique = nullptr;
