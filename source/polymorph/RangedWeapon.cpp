#include "RangedWeapon.h"

  RangedWeapon::RangedWeapon() : Weapon() {
  }

  RangedWeapon::RangedWeapon(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level): Weapon(TEquipablePrototype &prototype, char*name, char* manufacturer, int level) {
    _distance = prototype._distance;
  }

  RangedWeapon::~RangedWeapon() {
  }

  int RangedWeapon::get_distance() {
    return _distance;
  }
