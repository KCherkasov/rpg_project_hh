#include "Weapon.h"

  Weapon::Weapon(): EquipableItem() {
    _damage = new int[PAIR_ARR_SIZE];
  }

  Weapon::Weapon(TEquipablePrototype &prototype, unsigned char* name, unsigned char* manufacturer, int level): EquipableItem() {
    _damage = new int[PAIR_ARR_SIZE];
    _damage[0] = prototype._damdef;
    _damage[1] = _damage[0] * ITEM_DAMAGE_MINMAX_RATIO;
    delete[] _name;
    delete[] _manufacturer_id;
    _name = new unsigned char[NAMESTRING_SIZE];
    _manufacturer_id = new unsigned char[NAMESTRING_SIZE];
	for (size_t i = 0; i < STATS_COUNT; ++i) {
	  _stat_bons[i] = prototype._stat_bons[i];
	  _stat_reqs[i] = prototype._stat_reqs[i];
	}
	for (size_t i = 0; i < NAMESTRING_SIZE && name[i] == '\0'; ++i) {
      _name[i] = prototype._name[i];
      _manufacturer_id[i] = prototype._manufacturer[i];
	}
	for(size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
	  _description[i] = prototype._description[i];
	}
	_kind = TEquipmentKind(prototype.kind);
	_level = level;
	_cost = prototype._cost;
	//weapon rarity setting code here
	if (_level > START_LEVEL) {
      //weapon stats increasement code here
      for (size_t i = 0; i < _level; ++i) {
      	double tmp = _cost;
      	tmp *= COST_LEVEL_MODIFIER;
      	_cost = round(tmp);
      	for (size_t j = 0; j < CS_SIZE; ++j){
          tmp =  _stat_reqs[j];
          tmp *= STATS_LEVEL_MODIFIER;
          _stat_reqs[j] = round(tmp);
          tmp = _stat_bons[j];
          tmp *= STATS_LEVEL_MODIFIER;
          _stat_bons[j] = round(tmp);
        }
	    for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
          double tmp = _damage[i];
          tmp *= DAMDEF_LEVEL_MODIFIER;
          _damage[i] = tmp;
	    }
	  }
	}
  }

  Weapon::~Weapon() {
    delete[] _damage;
  }

  int* Weapon::get_damage() {
    int* res = new int[PAIR_ARR_SIZE];
    for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
      res[i] = _damage[i];
	}
	return res;
  }
  
  TEquipmentKind Weapon::get_kind() {
    return _kind;
  }
  
  int Weapon::what(std::string &out) {
	std::string handedness[PAIR_ARR_SIZE] {"two-handed", "one-handed"};
	std::string stat_names[CS_SIZE] {"accuracy: ","reaction: ","strength: ","toughness: ","awareness: ","intelligence: ","persuasion: ","speed: "};
    std::string kind_names[EK_SIZE] {"pistol","smg","assault rifle","sniper rifle","melee","light armour","medium armour","heavy armour", "trinket"};
	std::string slot_names[ES_SIZE] {"helmet","chest","gloves","boots","leg armour","trinket ","trinket ","trinket ","trinket ","main hand ","off-hand"};
	std::string lvl;
    std::string dmg;
    std::string cost;
    std::string dist;
    std::string req;
    std::string bon;
    lvl = "level: ";
    dmg = "damage: ";
    cost = "cost: ";
    dist = "distance: ";
    req = "--\nrequirements: ";
    bon = "--\nbonuses: ";
	std::string str;
	char* digit = new char[NAMESTRING_SIZE / 2];
    str.append((char*)_name); 
    str.append("\t");
	str.append((char*)_manufacturer_id);
	str.append("\n--\n");
    str += handedness[_slots[ES_WEAPON2]];
	str.append("\t");
	str += kind_names[_kind];
    str.append("\n");
    str += lvl;
	str.append(itoa(_level, digit, 10));
	str.append("\n");
    str += dmg;
	str.append(itoa(_damage[0], digit, 10));
	str.append("-");
	str.append(itoa(_damage[1], digit, 10));
	str.append("\n");
    str += cost;
	str.append(itoa(_cost, digit, 10));
	str.append("\n");
    str += req; 
	str.append("\n");
    for (size_t i = 0; i < CS_SIZE; ++i) {
      if (_stat_reqs[i] > 0) {
        str += stat_names[i];
		str.append(itoa(_stat_reqs[i], digit, 10));
        str.append("\n");
	  }
	}
	str += bon;
	str.append("\n");
    for (size_t i = 0; i < CS_SIZE; ++i) {
      if (_stat_bons[i] > 0) {
        str += stat_names[i];
		str.append(itoa(_stat_bons[i], digit, 10));
        str.append("\n");
	  }
	}
	str.append("\n");
	str.append("''");
	str.append((char*) _description);
	str.append("''");
	str.append("\n\n");
	delete[] digit;
	out.clear();
	out += str;
    return OK_CODE;
  }
  
  int Weapon::level_up() {
    //double stat_weights[CS_SIZE] {};
    return 0;
  }
