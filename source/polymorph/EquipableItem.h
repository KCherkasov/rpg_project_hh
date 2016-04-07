#include "UsableItem.h"

#pragma once

using namespace generic_consts;
using namespace prototypes;

  class EquipableItem: public UsableItem {
    public:
      EquipableItem();
      virtual ~EquipableItem();
      int* get_req_stats();
      int* get_bon_stats();
      char* get_manufacturer_id();
      int* get_slots();
    protected:
      int* _stat_reqs;
      int* _stat_bons;
      char* _manufacturer_id;
      int* _slots;
  };
  
