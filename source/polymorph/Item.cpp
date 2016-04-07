#include "Item.h"

  Item::Item() : StaticGameObject() {
    _cost = 0;
  }

  Item::~Item() {
  }

  int Item::get_cost() {
    return _cost;
  } 
  
  bool get_in_bag() {
    return _in_bag;
  }
