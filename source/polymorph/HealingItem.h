#include "ConsumableItem.h"

  class HealingItem: public ConsumableItem {
    public:
      HealingItem(TConsumablePrototype &prototype, int level);
      virtual ~HealingItem();
      int get_hp_restore();
      int use();
    protected:
      int* _hp_restore;
  };
