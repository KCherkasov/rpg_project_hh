#include "StaticGameObject.h"

class Location: StaticGameObject {
  public:
    Location();
    Location(TLocationPrototype &prototype, int level);
    virtual ~Location();
    virtual int entrance() = 0;
    int get_fight_chance() { return _fight_chance; }
    int get_low_level_cap() { return _low_level_cap; }
    int get_high_level_cap() { return _high_level_cap; }
  protected:
    int _fight_chance;
    int** _packs;
    int _low_level_cap;
    int _high_level_cap;
};

