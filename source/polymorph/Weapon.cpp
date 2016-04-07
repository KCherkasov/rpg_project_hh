#include "Weapon.h"

  Weapon::Weapon(): EquipableItem() {
    _damage = new int[PAIR_ARR_SIZE];
  }

  Weapon::Weapon(TEquipablePrototype &prototype, unsigned char* name, unsigned char* manufacturer, int level): EquipableItem() {
    _damage = new int[PAIR_ARR_SIZE];
    _damage[0] = prototype._damdef;
    _damage[1] = _damage[0] * ITEM_DAMAGE_MINMAX_RATIO;
	for (size_t i = 0; i < STATS_COUNT; ++i) {
	  _stat_bons[i] = prototype._stat_bons[i];
	  _stat_reqs[i] = prototype._stat_reqs[i];
	}
	for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
      _name[i] = name[i];
      _manufacturer_id[i] = manufacturer[i];
	}
	for(size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
	  _description[i] = prototype._description[i];
	}
	_kind = TEquipmentKind(prototype._kind);
	_level = level;
	//weapon rarity setting code here
	if (_level > START_LEVEL) {
      //weapon stats increasement code here
	}
  }

  Weapon::~Weapon() {
    delete[] _damage;
  }

  int* Weapon::get_damage() {
    int* res = new[PAIR_ARR_SIZE];
    for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
      res[i] = _damage[i];
	}
	return res;
  }
  
  TEquipmentKind Weapon::get_kind() {
    return _kind;
  }
  
  char* Weapon::what() {
  	char** stat_names = new [CS_SIZE][NAMESTRING_SIZE] {"accuracy:","reaction:","strength:","toughness:","awareness:","intelligence","persuasion","speed"};
    char** kind_names = new [EK_SIZE][NAMESTRING_SIZE] {"pistol","smg","assault rifle","sniper rifle","melee","light armour","medium armour","heavy armour", "trinket"};
	char** handedness = new [PAIR_ARR_SIZE][NAMESTRING_SIZE] {"two-handed", "one-handed"};
	char* lvl = new char[NAMESTRING_SIZE];
    char* dmg = new char [NAMESTRING_SIZE];
    char* cost = new char [NAMESTRING_SIZE];
    char* dist = new char [NAMESTRING_SIZE];
    char* req = new char[NAMESTRING_SIZE];
    char* bon = new char[NAMESTRING_SIZE];
    lvl = "level: ";
    dmg = "damage: ";
    cost = "cost: ";
    dist = "distance: ";
    req = "requirements: ";
    bon = "bonuses: ";
	std::string str;
	char* digit = new char[NAMESTRING_SIZE / 2];
    str += _name + "\t" + kind_names[_kind] + "\n--\n";
    str+= handedness[_slots[ES_WEAPON2]] + "\n";
    str += _manufacturer_id + "\n";
    str += lvl + itoa(_level, digit, 10) + "\n";
    str += dmg + itoa(_damage[0], digit, 10) + "-" + itoa(_damage[1], digit, 10) +"\n";
    if (_distance > 0) {
      str += dist + itoa(_distance, digit, 10) + "\n";
	}
    str += cost + itoa(_cost, digit, 10) + "\n";
    str += req + "\n";
    for (size_t i = 0; i < CS_SIZE; ++i) {
      if (_stat_reqs[i] > 0) {
        str += stat_names[i] + itoa(stat_reqs[i], digit, 10) + "\n";
	  }
	}
	str += bon + "\n";
    for (size_t i = 0; i < CS_SIZE; ++i) {
      if (_stat_bons[i] > 0) {
        str += stat_names[i] + itoa(stat_bons[i], digit, 10) + "\n";
	  }
	}
    for(size_t i = 0; i < CS_SIZE; ++i) {
      delete[] stat_names[i];
    }
    delete[] stat_names;
    for(size_t i = 0; i < EK_SIZE; ++i) {
      delete[] kind_names[i];
    }
    delete[] kind_names;
    for(size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
      delete[] handedness[i];
    }
    delete[] handedness;
    delete[] lvl;
    delete[] dmg;
    delete[] digit;
    delete[] cost;
    delete[] dist;
    delete[] req;
    delete[] bon;
    
    return str.data();
  }
