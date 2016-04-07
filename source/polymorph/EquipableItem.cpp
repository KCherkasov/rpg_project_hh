#include <ctime>
#include <cstdlib>

#include "EquipableItem.h"

  EquipableItem::EquipableItem(): UsableItem() {
    _stat_bons = new int[prototypes::STATS_COUNT];
    _stat_reqs = new int[prototypes::STATS_COUNT];
    _manufacturer_id = new char[NAMESTRING_SIZE];
    _slots = new int[ES_SIZE];
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
