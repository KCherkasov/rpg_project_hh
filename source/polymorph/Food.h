#include "ConsumableItem.h"

#pragma once

  class Food: public ConsumableItem {
    public:
      Food(prototypes::TConsumablePrototype &prototype, int level);
      virtual ~Food() {}
      int get_nutricity();
      int use() { return 0; }
    protected:
      int _nutricity;
  };

