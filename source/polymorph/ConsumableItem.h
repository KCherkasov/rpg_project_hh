#include "UsableItem.h"
#include <cmath>

#pragma once

  class ConsumableItem: public UsableItem {
    public:
      ConsumableItem();
      virtual ~ConsumableItem();
      int get_stack();
      int change_stack(int &value, bool increase);
      virtual int use() { return 0; }
    protected:
      int _stack;
  };
