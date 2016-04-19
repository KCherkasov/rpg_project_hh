#include "in_game_objects.h"

#pragma once

using namespace generic_consts;

namespace prototypes {

  const int PAIR_ARR_SIZE = 2;
  const int STATS_COUNT = 8;
  
  const int BACKPACK_SIZE = 36;
  const int STORAGE_SIZE = 72;
  const int BANK_SIZE = 154;
  
  const int VENDOR_CAPACITY = 154;
  
  const double ITEM_RARITY_MODIFIER = 0.25;
  const double ITEM_DAMAGE_MINMAX_RATIO = 1.25;
  
  const double DAMDEF_LEVEL_MODIFIER = 1.0625;
  const double COST_LEVEL_MODIFIER = 1.03;
  const double STATS_LEVEL_MODIFIER = 1.0625;
  
//  const double MANUFACTURER_BONUS = 1.13;

  enum TItemRareness { IR_TRASH, IR_COMMON, IR_GOOD, IR_RARE, IR_EPIC, IR_LEGENDARY };

  struct TConsumablePrototype {
  	char* _name;
  	char* _description;
	int _cost;
	int _effect;  
  };

  struct TCollectablePrototype {
    char* _name;
  	char* _description;
    int _cost;
    int _id;
  };

  struct TEquipablePrototype {
  	int _name_id; // set -1 if generated in-situ
  	int _manufacturer_id; // set -1 if generated in-situ
  	unsigned char* _description;
  	unsigned char* _name;
  	unsigned char* _manufacturer;
  	int _cost;
    int _damdef;
    int _distance;
    int _stat_reqs[STATS_COUNT];
    int _stat_bons[STATS_COUNT];
    int _slots[ES_SIZE];
    int kind;
  };

  struct TTilePrototype {
    int _texture;
    int _defense;
    bool _is_passable;
    unsigned char* _description;
    unsigned char* _name;
  };
  
  struct TNPCPrototype {
    int _content_id;
    int _charge; //set -1 for not traders
    unsigned char* _speech;
    unsigned char* _name;
  };

}
