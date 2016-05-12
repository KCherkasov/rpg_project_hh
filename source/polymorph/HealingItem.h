#include "ConsumableItem.h"

  class HealingItem: public ConsumableItem {
    public:
      HealingItem(TConsumablePrototype &prototype, int level);
      virtual ~HealingItem();
      int* get_hp_restore();
      int use(AliveGameObject* user);
      int what(std::string &out);
      int get_pic_name(std::string &out);
    protected:
      int* _hp_restore;
  };
