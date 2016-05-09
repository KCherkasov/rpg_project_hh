#include "AliveGameObject.h"

AliveGameObject::AliveGameObject(): GameObject() {
  _health = new int[PAIR_ARR_SIZE] {0};
  _exp = new int[PAIR_ARR_SIZE] {0};
}

AliveGameObject::~AliveGameObject() {
  delete[] _health;
  delete[] _exp;
}

int* AliveGameObject::get_health() {
  int* result = new int[PAIR_ARR_SIZE];
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    result[i] = _health[i];
  }
  return result;
}

int AliveGameObject::set_health(int change) {
  _health[CURRENT_VALUE_INDEX] += change;
  if (_health[CURRENT_VALUE_INDEX] < 0) {
    _health[CURRENT_VALUE_INDEX] = 0;
  } else {
    if (_health[CURRENT_VALUE_INDEX] > _health[MAXIMAL_VALUE_INDEX]) {
      _health[CURRENT_VALUE_INDEX] = _health[MAXIMAL_VALUE_INDEX];
	}
  }
  return 0;
}

int* AliveGameObject::get_exp() {
  int* result = new int[PAIR_ARR_SIZE];
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    result[i] = _exp[i];
  }
  return result;
}

