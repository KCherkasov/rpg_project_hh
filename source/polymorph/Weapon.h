#include "EquipableItem.h"

#pragma once

using namespace generic_consts;
using namespace prototypes;

  class Weapon: public EquipableItem {
    public:
      Weapon();
      Weapon(TEquipablePrototype &prototype, char*name, char* manufacturer, int level);
      virtual ~Weapon();
      int* get_damage();
      bool get_one_handed();
      TEquipmentKind get_kind();
      char* what();
      int use() { return 0; }
    protected:
    	int* _damage;
    	bool _one_handed;
    	TEquipmentKind _kind;
  };

