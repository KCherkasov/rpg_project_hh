#ifndef MONSTER_H
#define MONSTER_H

#include "AliveGameObject.h"
#include "LocalMap.h"
#include "Item.h"
#include "Forge.h"
#include "Stash.h"
#include "prototypes.h"

#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>

class Monster : public AliveGameObject {
  public:
    Monster(): AliveGameObject() { _damage = new int[PAIR_ARR_SIZE]; }
	virtual ~Monster() { delete[] _damage; }
    virtual int decision() = 0;
    int get_cash() { return _cash; }
    int get_morale() { return _morale; }
    int get_in_pack_id() { return _in_pack_id; }
    int* get_damage();
    int get_defense() { return _defense; }
    int get_loot_list() { return _loot_list; }
    bool get_is_leader() { return _is_leader; }
    bool get_is_mass_leader() { return _is_mass_leader; }
    int generate_loot(Stash* stash); 
  protected:
  	int* _damage;
  	int _defense;
    int _cash;
    int _morale;
    int _in_pack_id;
    int _loot_list;
    bool _is_leader;
    bool _is_mass_leader;
    
    int where_am_i(LocalMap* &map, int &my_x, int &my_y);
    int look_around(LocalMap* &map, int &enemies_count, int** &enemies_coords, int &allies_count, int** &allies_coords, int* &closest_cover_coords, int* &biggest_cover_coords);
    int get_closest(int* &result_coords, int* &my_coords, int** &coords, int count_in_sight);
    int get_weakest(LocalMap* &map, int* &result_coords, int** &coords, int count_in_sight);
    virtual int evaluate(int to_x, int to_y, int &points) = 0;
    int get_distance(int my_x, in  my_y, int to_x, int to_y, int &result);
};

#endif
