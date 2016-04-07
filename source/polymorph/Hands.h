#include "Armour.h"

#pragma once

class Hands : public Armour {
  public:
    Hands(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level): Armour(prototype, name, manufacturer, level) {}
    ~Hands();
};
