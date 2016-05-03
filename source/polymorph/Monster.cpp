#include "Monster.h"

int Monster::get_damage() {
  int* result = new int[PAIR_ARR_SIZE];
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    result[i] = _damage[i];
  }
  return result;
}

int Monster::generate_loot(Stash* stash) {
  int response;
  int range = 2 * LEVEL_RANGE;
  srand(static_cast<unsigned int>(time(0)));
  Forge* forge = new Forge("classic2.db");
  TLootList list;
  list._loot = NULL;
  response = forge->MakeLootList(_loot_list, &list);
  for (size_t i = 0; i < LOOT_LIST_SIZE; ++i) {
    if (list._loot[i]._id != FREE_INDEX) {
      for (size_t i = 0; i < list._loot[i]._max_quant; ++i) {
        int rnd = rand() % PERCENT_CAP;
        if (rnd <= list._loot[i]._chance) {
          Item* new_item = NULL;
          int item_level = _level + (rand() % range - LEVEL_RANGE);
          response = forge->MakeItem(list._loot[i]._id, item_level, &new_item);
          stash->_stash.push_back(new_item);
          new_item = NULL;
		}
	  }
	}
  }
  delete forge;
  for (size_t i = 0; i < _level; ++i) {
    double tmp = list._cash;
    tmp *= CASH_RAISE;
    list._cash = round(tmp);
    tmp = list._exp;
    tmp *= EXP_RAISE;
    list._exp = round(tmp);
  }
  stash->add_cash(list._cash);
  stash->add_exp(list._exp);
  return response;
}

int Monster::where_am_i(LocalMap* &map, int &my_x, int &my_y) {
  my_x = FREE_INDEX;
  my_y = FREE_INDEX;
  for (size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
    for (size_t j = 0; j < LOCAL_MAP_WIDTH; ++j) {
      if (map->_map[i][j]->_on_tile == this) {
        my_x = i;
        my_y = j;
        break;
	  }
	}
	if (my_x != FREE_INDEX && my_y != FREE_INDEX) {
      break;
	}
  }
  return 0;
}

int Monster::look_around(LocalMap* &map, int &enemies_count, int** &enemies_coords, int &allies_count, int** &allies_coords, int* &closest_cover_coords, int* &biggest_cover_coords) {
  enemies_count = 0;
  allies_count = 0;
  enemies_coords = new int*[PLAYER_SQUAD_SIZE] {NULL};
  allies_coords = new int*[MAX_MONSTER_SQUADS * MONSTER_SQUAD_SIZE - 1];
  for (size_t i = 0; i < PLAYER_SQUAD_SIZE; ++ i) {
    enemies_coords[i] = new int[PAIR_ARR_SIZE] {FREE_INDEX, FREE_INDEX};
  }
  for (size_t i = 0; i < MAX_MONSTER_SQUADS * MONSTER_SQUAD_SIZE - 1; ++i) {
    allies_coords[i] = new int[PAIR_ARR_SIZE] {FREE_INDEX, FREE_INDEX};
  }
  delete[] closest_cover_coords;
  delete[] biggest_cover_coords;
  closest_cover_coords = new int[PAIR_ARR_SIZE] {FREE_INDEX, FREE_INDEX};
  biggest_cover_coords = new int[PAIR_ARR_SIZE] {FREE_INDEX, FREE_INDEX};
  int distance_to_closest_cover;
  if (LOCAL_MAP_HEIGHT >= LOCAL_MAP_WIDTH) {
    distance_to_closest_cover = LOCAL_MAP_HEIGHT;
  } else {
    distance_to_closest_cover = LOCAL_MAP_WIDTH;
  }
  int biggest_cover_defense = map->_map[i][j]->get_defense();
  int* my_coords = new int[PAIR_ARR_SIZE];
  int response = where_am_i(my_coords[0], my_coords[1]);
  for (size_t i = my_coords[0]; (i < LOCAL_MAP_HEIGHT) && (BASIC_SIGHT_DISTANCE >= i - my_coords[0]); ++i) {
    for (size_t j = my_coords[1]; (j < LOCAL_MAP_WIDTH) && (BASIC_SIGHT_DISTANCE >= (i + j - my_coords[0] - my_coords[1])); ++j) {
      if (map->_map[i][j]->_on_tile == NULL) {
        int current_defense = map->_map[i][j]->get_defense();
        if (current_defense > biggest_cover_defense) {
          biggest_cover_defense = current_defense;
          biggest_cover_coords[0] = i;
          biggest_cover_coords[1] = j;
		}
		int current_cover_distance = get_distance(my_coords[0], my_coords[1], i , j);
		if (current_cover_distance < distance_to_closest_cover && current_defense < map->_map[i][j]->get_defense()) {
		  distance_to_closest_cover = current_cover_distance;
		  closest_cover_coords[0] = i;
		  closest_cover_coords[1] = j;
		}
	  } else {
        
	  }
	}
	for (size_t j = my_coords[1] - 1; (j >= 0) && (BASIC_SIGHT_DISTANCE >= (i + my_coords[1] - j - my_coords[0])); --j) {
      
	}
  }
  for (size_t i = my_coords[0] - 1; (i >= 0) && (BASIC_SIGHT_DISTANCE >= my_coords[0] - i); --i) {
    for (size_t j = my_coords[1]; (j < LOCAL_MAP_WIDTH) && (BASIC_SIGHT_DISTANCE >= (i + j - my_coords[0] - my_coords[1])); ++j) {
      
	}
	for (size_t j = my_coords[1] - 1; (j >= 0) && (BASIC_SIGHT_DISTANCE >= (i + my_coords[1] - j - my_coords[0])); --j) {
      
	}
  }
  delete[] my_coords;
  return response;
}

int Monster::get_closest(int* &result_coords, int* &my_coords, int** &coords, int count_in_sight) {
  delete[] result_coords;
  result_coords = new int[PAIR_ARR_SIZE] {coords[0][0], coords[0][1]};
  for (size_t i = 1; i < count_in_sight; ++i) {
    if (get_distance(my_coords[0], my_coords[1], coords[i][0], coords[i][1]) < get_distance(my_coords[0], my_coords[1], result_coords[0], result_coords[1])) {
      result_coords[0] = coords[i][0];
      result_coords[1] = coords[i][1];
	}
  }
  return 0;
}

int Monster::get_weakest(LocalMap* &map, int* &result_coords, int** &coords, int count_in_sight) {
  delete[] result_coords;
  result_coords = new int[PAIR_ARR_SIZE] {FREE_INDEX, FREE_INDEX};
  int lowest_hp = FREE_INDEX;
  for (size_t i = 0; i < count_in_sight; ++i) {
    if (map->_map[i][j]->_on_tile != NULL) {
      int* current_hp = NULL;
      current_hp = map->_map[coords[i][0]][coords[i][1]]->_on_tile->get_health();
      if (lowest_hp == current_hp[CURRENT_VALUE_INDEX]) {
        if (map->_map[result_coords[0]][result_coords[1]]->get_defense() < map->_map[coords[i][0]][coords[i][1]]->get_defense()) {
          result_coords[0] = coords[i][0];
          result_coords[1] = coords[i][1];
		}
	  }
	  if (lowest_hp == FREE_INDEX || current_hp[CURRENT_VALUE_INDEX] < lowest_hp) {
        lowest_hp = current_hp[CURRENT_VALUE_INDEX];
        result_coords[0] = coords[i][0];
        result_coords[1] = coords[i][1];
	  }
	  delete[] current_hp;
	}
  }
  return 0;
}

int Monster::get_distance(int my_x, int my_y, int to_x, int to_y, int &result) {
  int x_distance, y_distance;
  if (my_x >= to_x) {
    x_distance = my_x - to_x;
  } else {
    x_distance = to_x - my_x;
  }
  if (my_y >= to_y) {
    y_distance = my_y - to_y;
  } else {
    y_distance = to_y - my_y;
  }
  result = x_distance + y_distance;
  return 0;
}

