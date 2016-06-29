#pragma once

#ifndef CONSUMABLEITEM_H
#define CONSUMABLEITEM_H

#include "UsableItem.h"
#include <cmath>

  class ConsumableItem: public UsableItem {
    public:
      ConsumableItem(): UsableItem() {}
      virtual ~ConsumableItem() {}
      int get_stack() { return _stack; }
      int change_stack(int &value, bool increase) { return 0; }
      int get_pic_name(std::string &out) { return 0; }
    protected:
      int _stack;
  };
  
#endif
