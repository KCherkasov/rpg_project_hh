#include "Armour.h"

#pragma once

class Trinket: public Armour {
  public:
    Trinket(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level) : Armour(prototype, name, manufacturer, level) {}
    ~Trinket(){}
};
