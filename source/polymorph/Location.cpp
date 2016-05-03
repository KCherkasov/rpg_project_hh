#include "Location.h"

Location::Location(): StaticGameObject() {
  _packs = new int*[MAX_MONSTER_SQUADS] {NULL};
  for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    _packs[i] = new int[PAIR_ARR_SIZE] {0};
  }
}

Location::Location(TLocationPrototype &prototype, int level): StaticGameObject() {
  _low_level_cap = level - LEVEL_RANGE;
  _high_level_cap = level + LEVEL_RANGE;
  _fight_chance = prototype._fight_chance;
  _packs = new int*[MAX_MONSTER_SQUADS];
  for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    _packs[i] = new int[PAIR_ARR_SIZE];
    for(size_t j = 0; j < PAIR_ARR_SIZE; ++j) {
      _packs[i][j] = prototype._packs[i][j];
	}
  }
}

Location::~Location() {
  for(size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    delete[] _packs[i];
  }
  delete[] _packs;
}
