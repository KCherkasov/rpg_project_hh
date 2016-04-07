#include "Armour.h"

#pragma once

class Head: public Armour {
  public:
    Head(TEquipablePrototype &prototype, unsigned char* name, unsigned char* manufacturer, int level) : Armour(prototype, name, manufacturer, level) {}
    ~Head() {}
    int use();
};
