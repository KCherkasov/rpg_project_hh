#pragma once

#ifndef CONSUMABLEITEM_H
#define CONSUMABLEITEM_H

#include "UsableItem.h"
#include <cmath>

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
  
#endif
