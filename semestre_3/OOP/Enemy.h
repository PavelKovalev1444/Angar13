#ifndef ENEMY_H
#define ENEMY_H

#include "IEnemy.h"
class field;
class player;

template<typename T>
class Enemy:public IEnemy{
    T* type;
    field* fd;
    player& p;
public:
    int x;
    int y;
    int enemyHp = 100;
    Enemy(T* behave, int i, int j, field* f, player& pl);
    ~Enemy();
    void doSomething() override;
};

template<typename T>
Enemy<T>::Enemy(T* behave, int i, int j, field* f, player& pl): type(behave), x(j), y(i), fd(f), p(pl){}

template<typename T>
Enemy<T>::~Enemy() {
    delete type;
}

template<typename T>
void Enemy<T>::doSomething() {
    type->behave(fd, p, this, x, y);
}

#endif // ENEMY_H
