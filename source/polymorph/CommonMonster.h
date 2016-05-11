#ifndef COMMONMONSTER_H
#define COMMONMONSTER_H

#include "Monster.h"

class CommonMonster: public Monster {
  public:
  	CommonMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level);
  	virtual ~CommonMonster();
    int decision(Battlefield* &battlefield);
  protected:
    int evaluate(Battlefield* &battlefield, int &to_x, int &to_y, int &points);
};

#endif
