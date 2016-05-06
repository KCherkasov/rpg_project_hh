#include "GruntMonster.h"

GruntMonster::GruntMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level): Monster(prototype, name, faction, level) {
  double tmp;
  const unsigned char* role = "Grunt\0";
  for (size_t i = 0; i < NAMESTRING_SIZE && role[i] != '\0'; ++i) {
    _role[i] = role[i];
  }
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    tmp = _health[i];
    tmp *= GRUNT_HP_MODIFIER;
    _health[i] = round(tmp);
    tmp = _damage[i];
    tmp *= GRUNT_DMG_MODIFIER;
    _damage[i] = round(tmp);
  }
  tmp = _defense;
  tmp *= GRUNT_DEF_MODIFIER;
  _defense = round(tmp);
  delete[] role;
}
