#include "Armour.h"

#pragma once

class Legs: public Armour {
  public:
    Legs(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level) : Armour(prototype, name, manufacturer, level) {}
    ~Legs() {}
};  

