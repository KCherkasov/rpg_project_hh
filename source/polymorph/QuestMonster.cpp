#include "QuestMonster.h"

QuestMonster::QuestMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level, int quest_id): Monster(prototype, name, faction, level) {
  _quest_id = quest_id;
  const unsigned char* role = "Quest target\0";
  for (size_t i = 0; i < NAMESTRING_SIZE && role[i] != '\0'; ++i) {
    _role[i] = role[i];
  }
  double tmp;
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    tmp = _damage[i];
    tmp *= NONDEF_DMG_MODIFIER;
    _damage[i] = round(tmp);
    tmp = _health[i];
    tmp *= NONDEF_HP_MODIFIER;
    _health[i] = round(tmp);
  }
  tmp = _defense;
  tmp *= NONDEF_DEF_MODIFIER;
  _defense = round(tmp);
  delete[] role;
}
