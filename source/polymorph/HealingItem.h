#ifndef HEALING_ITEM_H
#define HEALING_ITEM_H

#include "ConsumableItem.h"
#include <ctime>

  class HealingItem: public ConsumableItem {
    public:
      HealingItem(TConsumablePrototype &prototype, int level): ConsumableItem() {}
      virtual ~HealingItem() {}
      int* get_hp_restore() { return _hp_restore; }
      int use(AliveGameObject* user) { return 0; }
      int what(std::string &out) { return 0; }
      int get_pic_name(std::string &out) { return 0; }
    protected:
      int* _hp_restore;
  };

#endif
