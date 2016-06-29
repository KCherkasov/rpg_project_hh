#ifndef COLLECTABLE_ITEM_H
#define COLLECTABLE_ITEM_H

#include "Item.h"
#include <cmath>

#pragma once

  class CollectableItem: public Item {
    public:
      CollectableItem(): Item() {}
      virtual ~CollectableItem() {}
      int get_stack() { return _stack; }
      int change_stack(int &value, bool increase) {
      	if (increase) {
           _stack += value;
		} else {
		  _stack -= value;
		}
	  }
    protected:
      int _stack;
  };
  
#endif
