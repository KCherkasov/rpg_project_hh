#pragma once

#ifndef FORGE_H
#define FORGE_H

#include "prototypes.h"
#include "RangedWeapon.h"
#include "MeleeWeapon.h"
#include "Head.h"
#include "Chest.h"
#include "Hands.h"
#include "Boots.h"
#include "Legs.h"
#include "Trinket.h"
#include "LocalMapObject.h"
#include "QuestGiver.h"
#include "ArmourTrader.h"
#include "WeaponTrader.h"
#include "MunitionsTrader.h"
#include "BlackMarket.h"
#include <wchar.h>
#include <cstdlib>
#include <ctime>
#include <direct.h>
#include <locale.h>

#include "sqlite3.h"

class Forge {
  public:
  	Forge();
  	Forge(const char* db_name);
  	~Forge();

  	int ConnectDatabase(const char* db_name);
  	int CloseDatabase();
  	int MakeItem(int query_id, int level, Item** spawned);
  	int MakeTile(int query_id, LocalMapObject** spawned);
  	int MakeNPC(int query_id, int level, NPC** spawned);
  	int MakeMask(int query_id, bool is_local, int** &spawned);
  	 
  private:
  	sqlite3* _database;
  	
  	int get_slots(int query_id, int* &slots);
  	int get_stat_reqs(int query_id, int* &reqs);
  	int get_stat_bons(int query_id, int* &bons);
  	
  	int get_manufacturer_data(int query_id, int kind, unsigned char* &manufacturer_name, double* bonus);
  	int get_item_name(int query_id, int item_kind, unsigned char* &item_name);
  	
  	int get_equipable_prototype(int query_id, TEquipablePrototype* prototype);
  	//int get_collectable_prototype(int query_id, TCollectablePrototype* prototype); //in development
  	//int get_consumable_prototype(int query_id, TConsumablePrototype* prototype);   //in development
  	
  	int get_local_map_mask(int query_id, int** &mask);
  	int get_global_map_mask(int query_id, int** &mask);
  	
  	int get_tile_prototype(int query_id, TTilePrototype* prototype);
  	
  	int get_npc_prototype(int query_id, TNPCPrototype* prototype);
  	
    int MakeEquipableItem(int query_id, int level, EquipableItem** spawned);
    //int MakeCollectableItem(int query_id, CoollectableItem* spawned); //in development
    //int MakeConsumableItem(int query_id, ConsumableItem* spawned);    //in development
};

#endif
