#include "Food.h"

  Food::Food(TConsumablePrototype &prototype, int level): ConsumableItem() {
  	_name = new unsigned char[NAMESTRING_SIZE];
    for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
      _name[i] = prototype._name[i];
      if (prototype._name[i] == '\0') {
        break;
	  }
	}
	_description = new unsigned char[DESCRSTRING_SIZE];
	for (size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
      _description[i] = prototype._description[i];
      if (prototype._description[i] == '\0') {
        break;
	  }
	}
	_nutricity = prototype._effect;
  }
  
  Food::~Food() {
  }
