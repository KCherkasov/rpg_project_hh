#include "Armour.h"

  Armour::Armour(): EquipableItem() {
  }
  
  Armour::Armour(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level): EquipableItem() {
    _defense = prototype._damdef;
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
	_kind = TEquipmentKind(prototype.kind);
	_level = level;
	//armour rarity setting code here
	if (_level > START_LEVEL) {
      //armour stats increasement code here
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
          _stat_reqs[j] = round(tmp);
        }
	  }
	  
        double tmp = _defense;
        tmp *= DAMDEF_LEVEL_MODIFIER;
        _defense = tmp;
	}
  }
  
  Armour::~Armour() {
  }
  
  int Armour::get_defense() {
    return _defense;
  }

  TEquipmentKind Armour::get_kind() {
    return _kind;
  }
  
  char* Armour::what() {
  	std::string stat_names[CS_SIZE] {"accuracy:","reaction:","strength:","toughness:","awareness:","intelligence","persuasion","speed"};
    std::string kind_names[EK_SIZE] {"pistol","smg","assault rifle","sniper rifle","melee","light armour","medium armour","heavy armour", "trinket"};
	std::string slot_names[ES_SIZE] {"helmet","chest","gloves","boots","leg armour","trinket ","trinket ","trinket ","trinket ","main hand ","off-hand"};
	std::string lvl;
    std::string def;
    std::string cost;
    std::string dist;
    std::string req;
    std::string bon;
    lvl = "level: ";
    def = "defense: ";
    cost = "cost: ";
    dist = "distance: ";
    req = "requirements: ";
    bon = "bonuses: ";
	std::string str;
	char* digit = new char[NAMESTRING_SIZE / 2];
    str.append((char*)_name); 
    str.append("\t");
	str += kind_names[_kind];
	str.append("\n--\n");
    for (size_t i = 0; i < ES_SIZE; ++i) {
      if (_slots[i] > 0) {
        str += slot_names[i];
        str.append("\n");
      	break;
	  }
	}
    str.append((char*)_manufacturer_id);
    str += lvl;
	str.append(itoa(_level, digit, 10));
	str.append("\n");
    str += def;
	str.append(itoa(_defense, digit, 10));
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
	delete[] digit;
    return const_cast<char*>(str.data());
  }
