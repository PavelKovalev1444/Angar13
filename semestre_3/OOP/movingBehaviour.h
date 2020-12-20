#ifndef MOVINGBEHAVIOUR_H
#define MOVINGBEHAVIOUR_H

class player;
class field;
class IEnemy;

class movingBehaviour{
public:
    movingBehaviour() = default;
    void behave(field* field, player& pl, IEnemy* enemy, int& xNow, int& yNow);
    void operator+= (player& pl);
};

#endif // MOVINGBEHAVIOUR_H
