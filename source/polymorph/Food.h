#pragma once

#ifndef FOOD_H
#define FOOD_H

#include "ConsumableItem.h"

  class Food: public ConsumableItem {
    public:
      Food(prototypes::TConsumablePrototype &prototype, int level): ConsumableItem() {}
      virtual ~Food() {}
      int get_nutricity() { return _nutricity; }
      int use(AliveGameObject* user) { return 0; }
      int what(std::string &out) { return 0; }
      int get_pic_name(std::string &out) { return 0; }
    protected:
      int _nutricity;
  };

#endif
