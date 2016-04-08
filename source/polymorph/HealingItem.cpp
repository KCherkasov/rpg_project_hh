#include "HealingItem.h"

  HealingItem::HealingItem(TConsumablePrototype &prototype, int level): ConsumableItem() {
  	_name = new unsigned char[NAMESTRING_SIZE];
    for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
      _name[i] = prototype._name[i];
      if (prototype._name[i] == '\0') {
        break;
	  }
	}
	_description = new unsigned char[DESCRSTRING_SIZE];
	for (size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
      _description[i] = prototype._description[i];
      if (prototype._description[i] == '\0') {
        break;
	  }
	}
	_stack = MIN_CONSUMABLE_STACK;
	_hp_restore = new int[PAIR_ARR_SIZE];
	_hp_restore[0] = prototype._effect;
    _hp_restore[1] = _hp_restore[0] * ITEM_DAMAGE_MINMAX_RATIO;
  }
  
  HealingItem::~HealingItem() {
  	delete[] _hp_restore;
  }
  
  int* HealingItem::get_hp_restore() {
    return _hp_restore;
  }
  
  int HealingItem::use() {
    
  }
