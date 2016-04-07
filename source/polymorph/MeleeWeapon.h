#include "Weapon.h"

#pragma once

  class MeleeWeapon: public Weapon {
    public:
      MeleeWeapon();
      MeleeWeapon(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level);
      virtual ~MeleeWeapon();
  };
