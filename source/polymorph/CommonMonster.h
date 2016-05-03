#ifndef COMMONMONSTER_H
#define COMMONMONSTER_H

#include "Monster.h"

class CommonMonster: public Monster {
  public:
  	CommonMonster(TMonsterPrototype &prototype, int level);
  	virtual ~CommonMonster();
    int decision();
  protected:
    int evaluate(int to_x, int to_y, int &points);
};

#endif
