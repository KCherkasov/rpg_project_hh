#include "AliveGameObject.h"

AliveGameObject::AliveGameObject(): GameObject() {
  _health = new int[PAIR_ARR_SIZE];
  _exp = new int[PAIR_ARR_SIZE];
  _stats = new int [CS_SIZE];
  _bag = new Storage(BACKPACK_SIZE);
  _equipped = new Equipped();
}

AliveGameObject::~AliveGameObject() {
  delete[] _health;
  delete[] _exp;
  delete[] _stats;
  delete _bag;
  delete _equipped;
}

int* AliveGameObject::get_health() {
  int* result = new int[PAIR_ARR_SIZE];
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    result[i] = _health[i];
  }
  return result;
}

int* AliveGameObject::get_exp() {
  int* result = new int[PAIR_ARR_SIZE];
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    result[i] = _exp[i];
  }
  return result;
}

int AliveGameObject::get_stat(int index, int &result) {
  if (index < 0 || index >= CS_SIZE) {
    return 0;
  }
  result = _stats[index];
  return 0;
}

int* get_stats() {
  int* result = new int[CS_SIZE];
  for (size_t i = 0; i < CS_SIZE; ++i) {
    result[i] = _stats[i];
  }
  return result;
}
