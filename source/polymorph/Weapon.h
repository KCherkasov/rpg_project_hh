#include "EquipableItem.h"
#include <string>

#pragma once

using namespace generic_consts;
using namespace prototypes;

  class Weapon: public EquipableItem {
    public:
      Weapon();
      Weapon(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level);
      virtual ~Weapon();
      int* get_damage();
      bool get_one_handed();
      TEquipmentKind get_kind();
      int what(std::string &out);
      int use() { return 0; }
    protected:
    	int* _damage;
    	bool _one_handed;
    	TEquipmentKind _kind;
    	int level_up();
  };

