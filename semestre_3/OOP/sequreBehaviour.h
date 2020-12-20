#ifndef SEQUREBEHAVIOUR_H
#define SEQUREBEHAVIOUR_H

class player;
class field;
class IEnemy;

class secureBehaviour{
public:
    secureBehaviour() = default;
    void behave(field* fieldPtr, player& pl, IEnemy* enemy, int xNow, int yNow);
    void operator+= (player& pl);
    void operator+= (IEnemy* enemy);
};


#endif // SEQUREBEHAVIOUR_H
