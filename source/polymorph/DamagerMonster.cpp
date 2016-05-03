#ifndef DAMAGERMONSTER_H
#define DAMAGERMONSTER_H

#include "Monster.h"

class DamagerMonster: public Monster {
  public:
  	DamagerMonster();
  	virtual ~DamagerMonster();
    int decision();
  protected:
    int where_am_i(LocalMap* &map);
    int look_around(LocalMap* &map, int &enemies_count, int** &enemies_coords, int &allies_count, int** &allies_coords);
    int get_closest(AliveGameObject* &result);
    int get_weakest(AliveGameObject* &result);
    int get_distance(int to_x, int to_y);
    int evaluate(AliveGameObject* &target, int &points);
    int evaluate(int to_x, int to_y, int &points);
};

#endif
