#ifndef DAMAGERMONSTER_H
#define DAMAGERMONSTER_H

#include "Monster.h"

class DamagerMonster: public Monster {
  public:
  	DamagerMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level);
  	virtual ~DamagerMonster();
    int decision(Battlefield* &battlefield);
  protected:
    int evaluate(Battlefield* &battlefield, int &to_x, int &to_y, int &points);
};

#endif
