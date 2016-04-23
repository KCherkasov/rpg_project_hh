#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"

  class Inventory {
    public:
      virtual int add_item(Item* new_item) = 0;
      virtual int remove_item(Item* to_delete) { delete to_delete; return 0; }
      virtual int swap_items(int from_slot, Inventory* to_bag, int to_slot) = 0;
      virtual int swap_items(Item* from, Item* to);
      virtual int use_item(Item* to_use) { return to_use->use(); }
      virtual void render() = 0;
      virtual Item* get_item(int index) = 0;
  };
  
#endif
