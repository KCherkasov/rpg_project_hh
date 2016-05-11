#include "CommonMonster.h"

CommonMonster::CommonMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level): Monster(prototype, name, faction, level) {
  const unsigned char* role = "Common\0";
  for (size_t i = 0; i < NAMESTRING_SIZE && role[i] != '\0'; ++i) {
    _role[i] = role[i];
  }
  double tmp;
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    tmp = _damage[i];
    tmp *= NONDEF_DMG_MODIFIER;
    _damage[i] = round(tmp);
    tmp = _health[i];
    tmp *= NONDEF_HP_MODIFIER;
    _health[i] = round(tmp);
  }
  tmp = _defense;
  tmp *= NONDEF_DEF_MODIFIER;
  _defense = round(tmp);
  delete[] role;
}

int CommonMonster::decision(Battlefield* &battlefield) {
  int my_coords = new int[PAIR_ARR_SIZE];
  where_am_i(battlefield->_map, my_coords[0], my_coords[1]);
  int to_x = FREE_INDEX;
  int to_y = FREE_INDEX;
  
  int** enemies_coords;
  int** allies_coords;
  
  int* closest_cover_coords;
  int* biggest_cover_coords;
  int* weakest_enemy_coords;
  int* closest_enemy_coords;
  // currently in development - logic of monsters interaction with each other
  // int* weakest_ally_coords;
  // int* closest_ally_coords;
  
  int allies_in_sight;
  int enemies_in_sight;
  
  int closest_cover_points;
  int biggest_cover_points;
  int weakest_enemy_points;
  int closest_enemy_points;
  // currently in development - logic of monsters interaction with each other
  // int weakest_ally_points;
  // int closest_ally_points;
  
  look_around(battlefield, enemies_in_sight, enemies_coords, allies_in_sight, allies_coords, closest_cover_coords, biggest_cover_coords);
  get_weakest(battlefield->_map, weakest_enemy_coords, enemies_coords, enemies_in_sight);
  get_closest(closest_enemy_coords, my_coords, enemies_coords, enemies_in_sight);
  // currently in development - logic of monsters interaction with each other
  // get_weakest(battlefield->_map, weakest_ally_coords, allies_coords, allies_in_sight);
  // get_closest(closest_ally_coords, my_coords, allies_coords, allies_in_sight);
  
  evaluate(battlefield, closest_enemy_coords[0], closest_enemy_coords[1], closest_enemy_points);
  evaluate(battlefield, weakest_enemy_coords[0], weakest_enemy_coords[1], weakest_enemy_points);
  evaluate(battlefield, closest_cover_coords[0], closest_cover_coords[1], closest_cover_points);
  evaluate(battlefield, biggest_cover_coords[0], closest_cover_coords[1], biggest_cover_points);
  // currently in development - logic of monsters interaction with each other
  // evaluate(battlefield, closest_ally_coords[0], closest_ally_coords[1], closest_ally_points);
  // evaluate(battlefield, weakest_ally_coords[0], weakest_ally_coords[1], weakest_ally_points);
  
  closest_enemy_points *= NONDEF_ATTACK_COST;
  weakest_enemy_points *= NONDEF_ATTACK_COST;
  closest_cover_points *= NONDEF_COVER_COST;
  biggest_cover_points *= NONDEF_COVER_COST;
  
  delete[] closest_cover_coords;
  delete[] biggest_cover_coords;
  delete[] closest_enemy_coords;
  delete[] weakest_enemy_coords;
  for(size_t i = 0; i < PLAYER_SQUAD_SIZE; ++i) {
    if (enemies_coords[i] != NULL) {
      delete[] enemies_coords[i];
	}
  }
  delete[] enemies_coords;
  for(size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    if (allies_coords[i] != NULL) {
      delete[] allies_coords[i];
	}
  }
  delete[] allies_coords;
  delete[] my_coords;
  // delete[] closest_ally_coords;
  // delete[] weakest_ally_coords;
  return 0;
}

int CommonMonster::evaluate(Battlefield* &battlefield, int &to_x, int &to_y, int &points) {
  points = 0;
  if (battlefield != NULL) {
    if  (to_x > FREE_INDEX && to_x < LOCAL_MAP_HEIGHT && to_y > FREE_INDEX && to_y < LOCAL_MAP_WIDTH) {
      if (battlefield->_map != NULL) {
      	int my_x;
        int my_y;
      	where_am_i(battlefield->_map, my_x, my_y);
		int distance;
        get_distance(my_x, my_y, to_x, to_y, distance);
        if (battlefield->_map->_map[to_x][to_y]->_on_tile == NULL) {
          points += battlefield->_map->_map[to_x][to_y]->get_defense();
          if (distance <= BASIC_SPEED) {
            points += ONE_STEP_MODIFIER;
		  } else {
            int bonus = ONE_STEP_MODIFIER / (distance / BASIC_SPEED);
            points += bonus;
		  }
		  if (!battlefield->_map->_map[to_x][to_y]->get_is_passable()) {
            srand(static_cast<unsigned int>(time(0)));
            int rnd = rand() % PERCENT_MOD_CAP;
            if (rnd <= PERCENT_MOD_CAP / 2) {
              if (to_x > my_x) {
              	--to_x;
			  } else {
                ++to_x;
			  }
			} else {
              if (to_y > my_y) {
                --to_y;
			  } else {
                ++to_y;
			  }
			}
		  }
		} else {
          int is_merc;
          battlefield->_player->_squad->get_member_index(battlefield->_map->_map[to_x][to_y]->_on_tile, is_merc);
		  if (is_merc != FREE_INDEX) {
            if (_distance <= distance) {
              points = PERCENT_MOD_CAP;
              points -= distance;
              points -= battlefield->_map->_map[to_x][to_y]->get_defense();
              int* health = battlefield->_map->_map[to_x][to_y]->_on_tile->get_health();
              points += health[MAXIMAL_VALUE_INDEX];
              points -= health[CURRENT_VALUE_INDEX];
              if (_damage[0] >= health[MAXIMAL_VALUE_INDEX] - health[CURRENT_VALUE_INDEX]) {
                points += ONE_SHOOT_MODIFIER;
			  } else {
                if (_damage[1] >= health[MAXIMAL_VALUE_INDEX] - health[CURRENT_VALUE_INDEX]) {
                  points += ONE_SHOOT_MODIFIER / 2;
				}
			  }
              delete[] health;
			}
		  } else {
            //some code for interaction with allies here (don't sure if common monster should act like that anyways)
		  }
		}
	  }
	}
  }
  // TO-DO: add flee logic, something like this - get closest enemy coords and move from that point at maximal distance.
  return 0;
}
