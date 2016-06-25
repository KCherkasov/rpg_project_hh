#include "Monster.h"

Monster::Monster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level)::AliveGameObject() {
  srand(static_cast<unsigned int>(time(0)));
  _damage = new int[PAIR_ARR_SIZE] {0};
  _faction = new unsigned char[NAMESTRING_SIZE] {};
  _role = new unsigned char[NAMESTRING_SIZE] {};
  for (size_t i = 0; i < NAMESTRING_SIZE; ++i ) {
    _name[i] = name[i];
    _faction[i] = faction[i];
  }
  _damage[CURRENT_VALUE_INDEX] = prototype._damage;
  _health[MAXIMAL_VALUE_INDEX] = prototype._hp;
  _defense = prototype._defense;
  _loot_list = prototype._loot_list_id;
  _initiative = prototype._initiative;
  _if_leader = false;
  _is_mass_leader = false;
  _morale = MAX_MORALE_VALUE;
  _in_pack_id = FREE_INDEX;
  _pick_id =  rand() % MONSTER_FACES_COUNT;
  if (_level > START_LEVEL) {
    for (size_t i = 0; i < _level; ++ i) {
      double tmp = _defense;
      tmp *= DAMDEF_LEVEL_MODIFIER;
      _defense = round(tmp);
      tmp = _damage[CURRENT_VALUE_INDEX];
      tmp *= DAMDEF_LEVEL_MODIFIER;
      _damage[CURRENT_VALUE_INDEX] = round(tmp);
      _health[MAXIMAL_VALUE_INDEX] += HP_RAISE_PER_LEVEL;
	}
  }
  _health[CURRENT_VALUE_INDEX] = _health[MAXIMAL_VALUE_INDEX];
  {
  	double tmp_dmg = _damage[CURRENT_VALUE_INDEX];
  	tmp_dmg *= ITEM_DAMAGE_MINMAX_RATIO;
  	_damage[MAXIMAL_VALUE_INDEX] = round(tmp_dmg);
  }
}

Monster::~Monster() {
  delete[] _damage;
  delete[] _faction;
  delete[] _role;
}

int Monster::try_make_leader() {
  srand(static_cast<unsigned int>(time(0)));
  int dice_roll = rand() % PERCENT_MOD_CAP;
  if (dice_roll <= BASE_LEADER_PROB) {
    for (size_t i = 0 ; i < PAIR_ARR_SIZE; ++i) {
      double tmp = _damage[i];
      tmp *= LEADER_DMG_MODIFIER;
      _damage[i] = round(tmp);
	}
	double tmp = _health[MAXIMAL_VALUE_INDEX];
	tmp *= LEADER_HP_MODIFIER;
	_health[MAXIMAL_VALUE_INDEX] = round(tmp);
	_health[CURRENT_VALUE_INDEX] = _health[MAXIMAL_VALUE_INDEX];
	tmp = _defense;
	tmp *= LEADER_DEF_MODIFIER;
	_defense =round(tmp);
	_is_leader = true;
  }
  return 0;
}

int Monster::try_make_mass_leader() {
  srand(static_cast<unsigned int>(time(0)));
  int dice_roll = rand() % PERCENT_MOD_CAP;
  if (dice_roll <= BASE_MASS_LEADER_PROB && is_leader) {
    for (size_t i = 0 ; i < PAIR_ARR_SIZE; ++i) {
      double tmp = _damage[i];
      tmp *= MASS_LEADER_DMG_MODIFIER;
      _damage[i] = round(tmp);
	}
	double tmp = _health[MAXIMAL_VALUE_INDEX];
	tmp *= MASS_LEADER_HP_MODIFIER;
	_health[MAXIMAL_VALUE_INDEX] = round(tmp);
	_health[CURRENT_VALUE_INDEX] = _health[MAXIMAL_VALUE_INDEX];
	tmp = _defense;
	tmp *= MASS_LEADER_DEF_MODIFIER;
	_defense =round(tmp);
	_is_mass_leader = true;
  }
  return 0;
}

int Monster::count_damage() {
  srand(static_cast<unsigned int>(time(0)));
  int damage = rand() % (_damage[1] - _damage[0]) + _damage[0];
  return damage;
}

bool Monster::make_hit_roll(int distance) {
	srand(static_cast<unsigned int>(time(0)));
	bool if_hit = false;
	int hit_roll = rand() % PERCENT_MOD_CAP;
    int hit_chance = PERCENT_MOD_CAP / 2 - distance + rand() % (PERCENT_MOD_CAP / 5);
    if_hit = hit_roll <= hit_chance;
	return if_hit;  
}

int* Monster::get_damage() {
  int* result = new int[PAIR_ARR_SIZE];
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    result[i] = _damage[i];
  }
  return result;
}

int Monster::generate_loot(Stash* &stash) {
  int response;
  int range = 2 * LEVEL_RANGE;
  srand(static_cast<unsigned int>(time(0)));
  Forge* forge = new Forge("classic2.db");
  TLootList list;
  list._loot = NULL;
  if (_loot_list != FREE_INDEX) {
  	response = forge->MakeLootList(_loot_list, &list);
  } else {
    response = forge->MakeLootList(rand() % LOOT_LISTS_COUNT + 1, &list);	
  }
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
  if (_is_leader) {
    double tmp = list._cash;
    tmp *= LEADER_CASH_MODIFIER;
    list._cash = round(tmp);
    tmp = list._exp;
    tmp *= LEADER_EXP_MODIFIER;
    list._exp = round(tmp);
    if (_is_mass_leader) {
      tmp = list._cash;
      tmp *= MASS_LEADER_CASH_MODIFIER;
      list._cash = round(tmp);
      tmp = list._exp;
      tmp *= MASS_LEADER_EXP_MODIFIER;
      list._exp = round(tmp);
	}
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

int Monster::look_around(Battlefield* &battlefield, int &enemies_count, int** &enemies_coords, int &allies_count, int** &allies_coords, int* &closest_cover_coords, int* &biggest_cover_coords) {

  return response;
}

int Monster::get_closest(int* &result_coords, int* &my_coords, int** &coords, int count_in_sight) {

  return 0;
}

int Monster::get_distance(int my_x, int to_x, int &result) {
  int x_distance, y_distance;
  if (my_x >= to_x) {
    x_distance = my_x - to_x;
  } else {
    x_distance = to_x - my_x;
  }
  result = x_distance;
  return 0;
}

int Monster::what(std::string &out) {
  char* digit = new char[NAMESTRING_SIZE / 2];
  out.clear();
  std::string str;
  str.clear();
  str.append((char*) _name);
  str.append("\t");
  str.append((char*) _role);
  str.append("\t level: ");
  str.append(itoa(_level, digit, 10));
  str.append("\n--\n");
  if(_is_leader) {
    str.append("pack leader\n");
  }
  if (_is_mass_leader) {
    str.append("group leader\n");
  }
  str.append("faction: ");
  str.append((char*) _faction);
  str.append("\n");
  str.append("health: ");
  str.append(itoa(_health[CURRENT_VALUE_INDEX], digit, 10));
  str.append(" / ");
  str.append(itoa(_health[MAXIMAL_VALUE_INDEX], digit, 10));
  str.append("\n");
  str.append("damage: ");
  str.append(itoa(_damage[CURRENT_VALUE_INDEX], digit, 10));
  str.append(" - ");
  str.append(itoa(_damage[MAXIMAL_VALUE_INDEX], digit, 10));
  str.append("\n");
  str.append("distance: ");
  str.append(itoa(_distance, digit, 10));
  str.append("\n");
  str.append("defense: ");
  str.append(itoa(_defense, digit, 10));
  str.append("\n");
  out += str;
  delete[] digit;
  return 0;
}

int Monster::get_pic_name(std::string &out) {
  out.clear();
  std::string prefix;
  std::string exec;
  prefix = "monster_face_";
  exec = ".png";
  char* digit = new char[NAMESTRING_SIZE];
  out += prefix;
  out.append(itoa(_pic_id, digit, 10));
  out += exec;
  delete[] digit;
  return 0;
}
