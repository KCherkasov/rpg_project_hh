#pragma once

#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "in_game_objects.h"

using namespace generic_consts;

namespace prototypes {

  const int PAIR_ARR_SIZE = 2;
  const int STATS_COUNT = 8;
  
  const int CONSUMABLES_COUNT = 6;
  
  const int BACKPACK_SIZE = 36;
  const int STORAGE_SIZE = 72;
  const int BANK_SIZE = 154;
  const int LOOT_LIST_SIZE = 16;
  
  const int VENDOR_CAPACITY = 154;
  const int BASIC_VENDOR_CHARGE = 10;
  
  const double ITEM_RARITY_MODIFIER = 0.25;
  const double ITEM_DAMAGE_MINMAX_RATIO = 1.25;
  
  const double DAMDEF_LEVEL_MODIFIER = 1.0625;
  const double COST_LEVEL_MODIFIER = 1.03;
  const double STATS_LEVEL_MODIFIER = 1.0625;
  
  const double CASH_RAISE = 1.10;
  const double EXP_RAISE = 1.10;
  
  const int BASE_NONDEF_PROB = 40;
  const int BASE_TANK_PROB = 20;
  const int BASE_SUPPORT_PROB = 20;
  const int BASE_DAMAGER_PROB = 20;

  const int BASE_LEADER_PROB = 10;
  const int BASE_MASS_LEADER_PROB = 20;

  const double NONDEF_HP_MODIFIER = 1.0;
  const double NONDEF_DMG_MODIFIER = 1.0;
  const double NONDEF_DEF_MODIFIER = 1.0;

  const double GRUNT_HP_MODIFIER = 1.50;
  const double GRUNT_DMG_MODIFIER = 0.50;
  const double GRUNT_DEF_MODIFIER = 2.25;

  const double SUPPORT_HP_MODIFIER = 0.75;
  const double SUPPORT_DMG_MODIFIER = 1.25;
  const double SUPPORT_DEF_MODIFIER = 0.50;

  const double DAMAGER_HP_MODIFIER = 0.50;
  const double DAMAGER_DMG_MODIFIER = 2.25;
  const double DAMAGER_DEF_MODIFIER = 0.75;
 
  const double LEADER_HP_MODIFIER = 1.50;
  const double LEADER_DMG_MODIFIER = 1.50;
  const double LEADER_DEF_MODIFIER = 1.50;
  const double LEADER_EXP_MODIFIER = 1.50;
  const double LEADER_CASH_MODIFIER = 1.50;

  const double MASS_LEADER_HP_MODIFIER = 1.25;
  const double MASS_LEADER_DMG_MODIFIER = 1.25;
  const double MASS_LEADER_DEF_MODIFIER = 1.25;
  const double MASS_LEADER_EXP_MODIFIER = 1.25;
  const double MASS_LEADER_CASH_MODIFIER = 1.25;

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
  
  struct TLoot {
    int _max_quant;
    int _chance;
    int _id;
  };

  struct TLootList {
    TLoot* _loot;
    int _cash;
    int _exp;
  };
  
  struct TLootListPrototype {
    int* _loot_ids;
    int _cash;
    int _exp;
  };
  
  struct TLocationPrototype {
    int** _packs;
    int* _trader_chances;
    int _fight_chance;
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
    unsigned char* _description;
  };
  
  struct TMonsterPrototype {
  	int _name_id; // set -1 if generated in-situ
    int _faction_id; // set -1 if generated in-situ
    int _hp;
    int _damage;
    int _defense;
    int _loot_list_id;
    int _decrement;
    int _initiative;
  };

}

#endif
