#include "CollectableItem.h"

CollectableItem::CollectableItem(): Item() {
    _stack = MIN_COLLECTABLE_STACK;
  }

  CollectableItem::~CollectableItem() {
  }

  int CollectableItem::get_stack() {
    return _stack;
  }
  
  int CollectableItem::change_stack(int &value, bool increase) {
  	int return_code = OK_CODE;
    if (increase) {
      _stack += value;
      if (_stack > MAX_COLLECTABLE_STACK) {
        value = _stack - MAX_COLLECTABLE_STACK;
        _stack = MAX_COLLECTABLE_STACK;
        return_code = OK_CODE;
	  } 
	} else {
      _stack -= value;
      if (_stack < MIN_COLLECTABLE_STACK) {
        value = abs(_stack) - MIN_COLLECTABLE_STACK;
        if (value > EMPTY_STACK) {
          return_code = OK_CODE;
        }
        _stack = EMPTY_STACK;
      }
    }
    return return_code;
  }
