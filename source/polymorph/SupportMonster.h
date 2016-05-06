#ifndef SUPPORTMONSTER_H
#define SUPPORTMONSTER_H

#include "Monster.h"

class SupportMonster: public Monster {
  public:
  	SupportMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level);
  	virtual SupportMonster();
    int decision();
  protected:
    int evaluate(int to_x, int to_y, int &points);
};

#endif
