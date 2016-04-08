#include "UsableItem.h"

#pragma once

  class ConsumableItem: public UsableItem {
    public:
      ConsumableItem();
      virtual ~ConsumableItem();
      int get_stack();
      int change_stack(int &value, bool increase);
      virtual int use() {}
    protected:
      int _stack;
  };
