#include "ConsumableItem.h"

  ConsumableItem::ConsumableItem(): UsableItem() {
    _stack = MIN_CONSUMABLE_STACK;
  }

  ConsumableItem::~ConsumableItem() {
  }

  int ConsumableItem::get_stack() {
    return _stack;
  }
  
  int ConsumableItem::change_stack(int &value, bool increase) {
  	int return_code = OK_CODE;
    if (increase) {
      _stack += value;
      if (_stack > MAX_CONSUMABLE_STACK) {
        value = _stack - MAX_CONSUMABLE_STACK;
        _stack = MAX_CONSUMABLE_STACK;
        return_code = OK_CODE;
	  } 
	} else {
      _stack -= value;
      if (_stack < MIN_CONSUMABLE_STACK) {
        value = abs(_stack) - MIN_CONSUMABLE_STACK;
        if (value > EMPTY_STACK) {
          return_code = OK_CODE;
        }
        _stack = EMPTY_STACK;
      }
    }
    return return_code;
  }

