#pragma once

#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "Weapon.h"

using namespace generic_consts;
using namespace prototypes;

  class RangedWeapon: public Weapon {
    public:
      RangedWeapon();
      RangedWeapon(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level);
      virtual ~RangedWeapon();
      int get_distance();
    protected:
      int _distance;
  };
  
#endif
