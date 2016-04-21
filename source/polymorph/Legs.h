#pragma once

#ifndef LEGS_H
#define LEGS_H

#include "Armour.h"

class Legs: public Armour {
  public:
    Legs(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level) : Armour(prototype, name, manufacturer, level) {}
    ~Legs() {}
};  

#endif
