#include "in_game_objects.h"      
      
  in_game_objects::GameObject::GameObject() : _own_id(++_id), _level(START_LEVEL), _name(NULL) {}

  in_game_objects::GameObject::GameObject(int inp_level): _own_id(++id), _level(inp_level), _name(NULL) {}
  
  in_game_objects::GameObject::~GameObject() {
    delete[] _name;
  }

  int in_game_objects::GameObject::get_id() {
    return _id;
  }

  int in_game_objects::GameObject::get_own_id() {
    return _own_id;
  }

  int in_game_objects::GameObject::get_level() {
    return _level;
  }

  char* in_game_objects::GameObject::get_name() {
    if (_name == NULL) { 
      char* res = _name; 
    } else {
      char* res = new char[NAMESTRING_SIZE];
      for (int i = 0; i < NAMESTRING_SIZE; ++i) {
        res[i] = _name[i];
      }
    }
    return res;
  }

  in_game_objects::StaticGameObject::StaticGameObject() : GameObject()  {
    _description = NULL;
  }

  in_game_objects::StaticGameObject::~StaticGameObject() {
  	delete[] _description;
  }

  char* in_game_objects::StaticGameObject::get_description() {
    if (_description == NULL) {
      return _description;
	} else {
      char* res = new char[DESCRSTRING_SIZE];
      for (int i = 0; i < DESCRSTRING_SIZE; ++i) {
        res[i] = _description[i];
	  }
	  return res;
	}
  }

  in_game_object::Item::Item() : StaticGameObject() {
    _cost = 0;
  }

  in_game_object::Item::~Item() {
  }

  int in_game_object::Item::get_cost() {
    return _cost;
  } 

  in_game_objects::UsableItem::UsableItem() : Item() {
     _level = START_LEVEL;
     _rarity = prototypes::IR_COMMON;
  }

  int_game_objects::UsableItem::~UsableItem() {
  }

  prototypes::TItemRareness in_game_objects::UsableItem::get_rarity {
    return _rarity;
  }

  in_game_objects::EquipableItem::EquipableItem(): UsableItem() {
    _stat_bons = new int[prototypes::STATS_COUNT];
    _stat_reqs = new int[prototypes::STATS_COUNT];
  }

  in_game_objects::EquipableItem::~EquipableItem() {
    delete[] _stat_bons;
    delete[] _stat_reqs;
  }

  int* in_game_objects::EquipableItem get_stat_bons() {
    int* res = new int[prototypes::STATS_COUNT];
    for (size_t i = 0; i < prototypes::STATS_COUNT; ++i) {
      res[i] = _stat_bons[i];
	}
	return res;
  }

  int* in_game_objects::EquipableItem get_stat_reqs() {
    int* res = new int[prototypes::STATS_COUNT];
    for (size_t i = 0; i < prototypes::STATS_COUNT; ++i) {
      res[i] = _stat_reqs[i];
	}
	return res;
  }

  in_game_objects::Weapon::Weapon(): EquipableItem() {
    _damage = new int[PAIR_ARR_SIZE];
  }

  in_game_objects::Weapon::Weapon(TEquipablePrototype &prototype, int level): EquipableItem() {
    _damage = new int[PAIR_ARR_SIZE];
    _manufacturer_id = prototype._manufacturer_id;
    _damage[0] = prototype._damdef;
    _damage[1] = _damage[0] * ITEM_DAMAGE_MINMAX_RATIO;
	for (size_t i = 0; i < STATS_COUNT; ++i) {
	  _stat_bons[i] = prototype._stat_bons[i];
	  _stat_reqs[i] = prototype._stat_reqs[i];
	}
	_kind = prototype._wkind;
	_level = level;
	//weapon rarity setting code here
	if (_level > START_LEVEL) {
      //weapon stats increasement code here
	}
  }

  in_game_objects::Weapon::~Weapon() {
    delete[] _damage;
  }

  int* in_game_objects::Weapon::get_damage() {
    int* res = new[PAIR_ARR_SIZE];
    for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
      res[i] = _damage[i];
	}
	return res;
  }

  in_game_objects::RangedWeapon::RangedWeapon() : Weapon() {
  }

  in_game_objects::RangedWeapon::RangedWeapon(TEquipablePrototype &prototype, int level): Weapon(TEquipablePrototype &prototype, int level) {
    _distance = prototype._distance;
  }

  in_game_objects::RangedWeapon::~RangedWeapon() {
  }

  int in_game_objects::RangedWeapon::get_distance() {
    return _distance;
  }
  
  in_game_objects::MeleeWeapon::MeleeWeapon() : Weapon() {
  }

  in_game_objects::MeleeWeapon::MeleeWeapon(TEquipablePrototype &prototype, int level): Weapon(TEquipablePrototype &prototype, int level) {
  }
  
  in_game_objects::MeleeWeapon::~Weapon() {
  }
  
  in_game_objects::Armour::Armour(): EquipableItem() {
  }
  
  in_game_objects::Armour::Armour(TEquipablePrototype &prototype, int level): EquipableItem() {
    _name_id = prototype._name_id;
	_manufacturer_id = prototype._manufacturer_id;
    _defense = prototype._damdef;
	for (size_t i = 0; i < STATS_COUNT; ++i) {
	  _stat_bons[i] = prototype._stat_bons[i];
	  _stat_reqs[i] = prototype._stat_reqs[i];
	}
	_kind = prototype._akind;
	_level = level;
	//weapon rarity setting code here
	if (_level > START_LEVEL) {
      //weapon stats increasement code here
	}
  }
  
  in_game_objects::Armour::~Armour() {
  }
  
  int in_game::Armour::get_defense() {
    return _defense;
  }

  prototypes::TArmourKind in_game_object::Armour::get_kind() {
    return _kind;
  }

  in_game_objects::ConsumableItem::ConsumableItem(): UsableItem() {
    _stack = 1;
  }

  in_game_objects::ConsumableItem::~UsableItem() {
  }

  int in_game_objects::ConsumableItem::get_stack() {
    return _stack;
  }

  in_game_objects::HealingItem::HealingItem(TConsumablePrototype &prototype, int level): ConsumableItem() {
    for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
      _name[i] = prototype._name[i];
      if (prototype._name[i] == '\0') {
        break;
	  }
	}
	for (size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
      _description[i] = prototype._description[i];
      if (prototype._description[i] == '\0') {
        break;
	  }
	}
	_stack = MIN_CONSUMABLE_STACK;
	_hp_restore[0] = prototype._effect;
    _hp_restore[1] = hp_restore[0] * ITEM_DAMAGE_MINMAX_RATIO;
  }
