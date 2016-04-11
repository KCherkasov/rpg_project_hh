#include "UsableItem.h"
#include <cstdlib>
#include <cmath>

#pragma once

using namespace generic_consts;
using namespace prototypes;

  class EquipableItem: public UsableItem {
    public:
      EquipableItem();
      virtual ~EquipableItem();
      int* get_stat_reqs();
      int* get_stat_bons();
      char* get_manufacturer_id();
      int* get_slots();
    protected:
      int* _stat_reqs;
      int* _stat_bons;
      unsigned char* _manufacturer_id;
      int* _slots;
      virtual int level_up() = 0;
  };
  
