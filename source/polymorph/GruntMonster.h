#ifndef GRUNTMONSTER_H
#define GRUNTMONSTER_H

#include "Monster.h"

class GruntMonster: public Monster {
  public:
  	GruntMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level);
  	virtual ~GruntMonster();
    int decision(Battlefield* &battlefield);
  protected:
    int evaluate(Battlefield* &battlefield, int &to_x, int &to_y, int &points);
};

#endif
