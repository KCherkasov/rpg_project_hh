#ifndef GRUNTMONSTER_H
#define GRUNTMONSTER_H

#include "Monster.h"

class GruntMonster: public Monster {
  public:
  	GruntMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level);
  	virtual ~GruntMonster();
    int decision();
  protected:
    int evaluate(int to_x, int to_y, int &points);
};

#endif
