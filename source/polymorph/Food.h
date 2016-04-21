#pragma once

#ifndef FOOD_H
#define FOOD_H

#include "ConsumableItem.h"

  class Food: public ConsumableItem {
    public:
      Food(prototypes::TConsumablePrototype &prototype, int level);
      virtual ~Food() {}
      int get_nutricity();
      int use() { return 0; }
    protected:
      int _nutricity;
  };

#endif
