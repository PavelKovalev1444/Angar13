#ifndef IENEMY_H
#define IENEMY_H

class IEnemy{
public:
    int enemyHp = 100;
    int x;
    int y;
    virtual void doSomething() = 0;
};


#endif // IENEMY_H
