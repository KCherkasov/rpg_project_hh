#include "Weapon.h"

#pragma once

using namespace generic_consts;
using namespace prototypes;

  class RangedWeapon: public Weapon {
    public:
      RangedWeapon();
      RangedWeapon(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level);
      //bool equip();
      virtual ~RangedWeapon();
      int get_distance();
    protected:
      int _distance;
  };
