#include "Item.h"

#pragma once

  class CollectableItem: public Item {
    public:
      CollectableItem();
      virtual ~CollectableItem();
      int get_stack();
      int change_stack(int &value, bool increase);
    protected:
      int _stack;
  };
