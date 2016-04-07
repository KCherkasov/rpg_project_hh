#include "EquipableItem.h" 

#pragma once   

  class Armour: public EquipableItem {
    public:
      Armour();
      Armour(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level);
      virtual ~Armour();
      int get_defense();
      TEquipmentKind get_kind();
      char* what();
      int use() { return 0; }
    protected:
      int _defense;
      TEquipmentKind _kind;
  };
