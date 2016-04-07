#include "Armour.h"

#pragma once

class Chest : public Armour {
  public:
    Chest(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level) : Armour(prototype, name, manufacturer, level) {}
    ~Chest() {}
};
