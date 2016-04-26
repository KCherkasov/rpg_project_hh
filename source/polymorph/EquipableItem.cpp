#include <ctime>
#include <cstdlib>

#include "EquipableItem.h"

  EquipableItem::EquipableItem(): UsableItem() {
    _stat_bons = new int[prototypes::STATS_COUNT];
    _stat_reqs = new int[prototypes::STATS_COUNT];
    _manufacturer_id = new unsigned char[NAMESTRING_SIZE];
    _slots = new int[ES_SIZE];
    _in_bag = true;
  }

  EquipableItem::~EquipableItem() {
    delete[] _stat_bons;
    delete[] _stat_reqs;
    delete[] _manufacturer_id;
    delete[] _slots;
  }

  int* EquipableItem::get_stat_bons() {
    int* res = new int[prototypes::STATS_COUNT];
    for (size_t i = 0; i < prototypes::STATS_COUNT; ++i) {
      res[i] = _stat_bons[i];
	}
	return res;
  }

  int* EquipableItem::get_stat_reqs() {
    int* res = new int[prototypes::STATS_COUNT];
    for (size_t i = 0; i < prototypes::STATS_COUNT; ++i) {
      res[i] = _stat_reqs[i];
	}
	return res;
  }
  
  char* EquipableItem::get_manufacturer_id() {
  	char* res = new char[NAMESTRING_SIZE];
  	for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
      res[i] = _manufacturer_id[i];
    }
    return res;
  }

  int* EquipableItem::get_slots() {
    int* res = new int[ES_SIZE];
    for (size_t i = 0; i < ES_SIZE; ++i) {
      res[i] = _slots[i];
	}
	return res;
  }
  
  bool EquipableItem::meets_stat_reqs(AliveGameObject* &user){
    int* stats = NULL;
    bool result = true;
    stats = user->get_stats();
    for (size_t i = 0; i < CS_SIZE; ++i) {
      result = result && (_stat_reqs[i] <= stats[i]);
	}
	return result;
  }
  
  int EquipableItem::use(AliveGameObject* &user) {
    if (_in_bag) {
      if (meets_stat_reqs(user)) {
      	int equipped_slot = FREE_INDEX;
      	for (size_t i = 0; i < ES_SIZE; ++i) {
      	  if (_slots[i] == 1 && equipped[i] == NULL) {
      	    equipped_slot = i;
      	    break;
		  }
		}
		if (equipped_slot == FREE_INDEX) {
          for (size_t i =0; i < ES_SIZE; ++i) {
            if (_slots[i] == 1) {
              equipped_slot = i;
              break;
			}
		  }
		}
        user->_bag->swap_items(user->_bag->get_index(this), user->_equipped, equipped_slot);
        _in_bag = !_in_bag;
	  }
	} else {
	  int free_slots;
	  user->_bag->count_free_slots(free_slots);
      if (free_slots > 0) {
      	int first_free = FREE_INDEX;
      	user->_bag->first_free_slot(first_free);
        user->_equipped->swap_items(user->_equipped->get_index(this), user->_bag, first_free);
        _in_bag = !_in_bag;
	  }
	}
	return 0;  
  }
