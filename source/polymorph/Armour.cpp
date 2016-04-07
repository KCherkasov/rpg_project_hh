#include "Armour.h"

  Armour::Armour(): EquipableItem() {
  }
  
  Armour::Armour(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level): EquipableItem() {
    _name_id = prototype._name_id;
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
	_kind = TEquipmentKind(prototype._kind);
	_level = level;
	//armour rarity setting code here
	if (_level > START_LEVEL) {
      //armour stats increasement code here
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
  	char** stat_names = new [CS_SIZE][NAMESTRING_SIZE] {"accuracy:","reaction:","strength:","toughness:","awareness:","intelligence","persuasion","speed"};
    char** kind_names = new [EK_SIZE][NAMESTRING_SIZE] {"pistol","smg","assault rifle","sniper rifle","melee","light armour","medium armour","heavy armour", "trinket"};
	char** slot_names = new [ES_SIZE][NAMESTRING_SIZE] {"helmet","chest","gloves","boots","leg armour","trinket ","trinket ","trinket ","trinket ","main hand ","off-hand"};
	char* lvl = new char[NAMESTRING_SIZE];
    char* def = new char [NAMESTRING_SIZE];
    char* cost = new char [NAMESTRING_SIZE];
    char* dist = new char [NAMESTRING_SIZE];
    char* req = new char[NAMESTRING_SIZE];
    char* bon = new char[NAMESTRING_SIZE];
    lvl = "level: ";
    def = "defense: ";
    cost = "cost: ";
    dist = "distance: ";
    req = "requirements: ";
    bon = "bonuses: ";
	std::string str;
	char* digit = new char[NAMESTRING_SIZE / 2];
    str += _name + "\t" + kind_names[_kind] + "\n--\n";
    for (size_t i = 0; i < ES_SIZE; ++i) {
      if (_slots[i] > 0) {
        str += slot_names[i] + "\n";
      	break;
	  }
	}
    str += _manufacturer_id + "\n";
    str += lvl + itoa(_level, digit, 10) + "\n";
    str += def + itoa(_defense, digit, 10) + "\n";
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
    for(size_t i = 0; i < ES_SIZE; ++i) {
      delete[] slot_names[i];
    }
    delete[] slot_names;
    delete[] lvl;
    delete[] def;
    delete[] digit;
    delete[] cost;
    delete[] dist;
    delete[] req;
    delete[] bon;
    
    return str.data();
  }
