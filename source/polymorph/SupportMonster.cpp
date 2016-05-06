#include "SupportMonster.h"

SupportMonster::SupportMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level): Monster(prototype, name, faction, level) {
  const unsigned char* role = "Support\0";
  for (size_t i = 0; i < NAMESTRING_SIZE && role[i] = '\0') {
    _role[i] = role[i];
  }
  double tmp;
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    tmp = _health[i];
    tmp *= SUPPORT_HP_MODIFIER;
    _health[i] = round(tmp);
    tmp = _damage[i];
    tmp *= SUPPORT_DMG_MODIFIER;
    _damage[i] = round(tmp);
  }
  tmp = _defense;
  tmp *= SUPPORT_DEF_MODIFIER;
  _defense = round(tmp);
  delete[] role;
}
