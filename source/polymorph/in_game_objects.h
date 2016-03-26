#include <ctime>
#inlcude <cstdlib>
#include "prototypes.h"

#pragma once

namespace in_game_objects {

  using namespace prototypes;

  const int MIN_COLLECTABLE_STACK = 1;
  const int MAX_COLLECTABLE_STACK = 200;
  
  const int MIN_CONSUMABLE_STACK = 1;
  const int MAX_CONSUMABLE_STACK = 200;
   
  const int START_LEVEL = 1;
  
  const int NAMESTRING_SIZE = 30;
  const int DESCRSTRING_SIZE = 300;

  class GameObject {
    public:
      GameObject();
      GameObject(int level);
      virtual ~GameObject()
      int get_id();
      int get_own_id();
      int get_level();
      char* get_name();

    protected:
      static int _id = -1;
      int _own_id;
      int _level;
      char* _name;
  };

  class StaticGameObject: public GameObject {
    public:
	  StaticGameObject();
	  virtual ~StaticGameObject();
	  char* get_description()
    protected:    
      char* _description;
  };

  class Item: public StaticGameObject {
    public:
      Item();
      virtual ~Item();
      int get_cost();
    protected:
      _cost: int;
  };
  
  class UsableItem: public Item {
    public:
      UsableItem();
      virtual ~UsableItem();
      prototypes::TItemRareness get_rarity();
      virtual int use() {}
    protected:
      TItemRareness _rarity;
  };

  class EquipableItem: public UsableItem {
    public:
      EquipableItem();
      virtual ~EquipableItem();
      virtual in_game_objects::TClassId get_class();
      virtual int equip() {}
      int* get_req_stats();
      int* get_bon_stats();
      int get_manufacturer_id();
    protected:
      int* _req_stats;
      int* _bon_stats;
      int _manufacturer_id;
  };
  
  class Weapon: public EquipableItem {
    public:
      Weapon();
      Weapon(TEquipablePrototype &prototype, int level);
      virtual ~Weapon();
      int* get_damage();
      bool get_one_handed();
      prototypes::TWeaponKind get_kind();
    protected:
    	int* _damage;
    	bool _one_handed;
    	TWeaponKind _kind;
  };
  
  class RangedWeapon: public Weapon {
    public:
      RangedWeapon();
      RangedWeapon(TEquipablePrototype &prototype, int level);
      bool equip();
      virtual ~RangedWeapon();
      int get_distance();
    protected:
      int _distance;
  };
  
  class MeleeWeapon: public Weapon {
    public:
      MeleeWeapon();
      MeleeWeapon(prototypes::TEquipablePrototype prototype, int level);
      virtual ~MeleeWeapon();
      bool equip();
  };
  
  class Armour: public EquipableItem {
    public:
      Armour();
      Armour(prototypes::TEquipablePrototype prototype, int level);
      virtual ~Armour();
      int get_defense();
      prototypes::TArmourKind get_kind();
    protected:
      int _defense;
      TArmourKind _kind;
  };

  class ConsumableItem: public UsableItem {
    public:
      ConsumableItem();
      virtual ~ConsumableItem();
      int get_stack();
      int inc_stack(int inc_number);
      int dec_stack(int dec_value);
      virtual int use() {}
    protected:
      int _stack;
  };

  class HealingItem: public ConsumableItem {
    public:
      HealingItem(prototypes::TConsumablePrototype &prototype, int level);
      virtual ~HealingItem();
      int get_hp_restore();
      int use();
    protected:
      int* _hp_restore;
  };

  class Food: public ConsumableItem {
    public:
      Food(prototypes::TConsumablePrototype &prototype, int level);
      virtual ~Food();
      int get_nutricity();
      int use();
    protected:
      int _nutricity;
  };

  class CollectableItem: public Item {
    public:
      CollectableItem();
      virtual ~CollectableItem();
      int get_stack();
      int inc_stack(int inc_number);
      int dec_stack(int dec_number);
    protected:
      int _stack;
  };

  class QuestItem: public CollectableItem {
    public:
      QuestItem(TCollectablePrototype &prototype);
      virtual ~QuestItem();
      int get_quest_id();
    protected:
      int _quest_id; //change to Quest* after Quest class development
  };

  class ResourceItem: public CollectableItem {
    public:
      ResourceItem(TCollectablePrototype &prototype);
      virtual ~ResourceItem();
      int get_resource_id();
    protected:
      int _resource_id;
  };

  class Inventory {
    public:
      virtual int add_item(Item* new_item) = 0;
      virtual int remove_item(Item* to_delete) { delete to_delete; return 0; }
      virtual int swap_items(Item* from, Item* to) = 0;
      virtual int use_item(Item* to_use) { to_use->use(); return 0; }
      virtual void render() = 0;
      virtual Item* get_item() = 0;
  };

  class AliveGameObject: public GameObject {
    public:
      AliveGameObject();
      virtual ~AliveGameObject();
      int* get_health();
      int* get_coords();
      int* get_exp();
      
      Inventory* inventory;
    protected:
      int* _health;
      int* _coords;
      int* _exp;
  };

}
