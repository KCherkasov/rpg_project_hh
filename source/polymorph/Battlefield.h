#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "Location.h"
#include "LocalMap.h"
#include "Stash.h"
#include "Squad.h"
#include "Player.h"
#include "Forge.h"
#include "Action.h"
#include "Attack.h"
#include "Move.h"
#include "prototypes.h"

#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>

class Battlefield {
  public:
    Battlefield();
    Battlefield(Location* location, Player* &player);
  	virtual ~Battlefield();
  	
    Squad* _squads;
    Action** _turn_queue;
    Stash* _stash;
    Player* _player;
    
    int make_turn();
    int if_end_fight(bool &is_victory, bool &is_end);
    
  protected:
  	int spawn_new_pack(int monster_id, bool target_there, int level, int squad_id);
  	int pack_set_leader(int pack_id);
  	int set_mass_leader();
  	int pack_has_leader(int pack_id, int &result_index);
  	int mass_leader_is_spawned(bool &result);
	int place_units_on_map();
  	int clear_dead();
  	int sort_turn_queue();	
  	int _turn_no;
};

#endif
