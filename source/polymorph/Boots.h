#include "Armour.h"

#pragma once

class Boots: public Armour {
  public:
    Boots(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level): Armour(prototype, name, manufacturer, level){}
    ~Boots(){}
};
