#ifndef STANDBEHAVIOUR_H
#define STANDBEHAVIOUR_H

class player;
class field;
class IEnemy;

class standBehaviour{
public:
    standBehaviour() = default;
    void behave(field* field, player& pl, IEnemy* enemy, int xNow, int yNow);
    void operator+= (player& pl);
};

#endif // STANDBEHAVIOUR_H
