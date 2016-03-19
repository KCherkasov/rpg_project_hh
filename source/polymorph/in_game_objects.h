#include <ctime>
#inlcude <cstdlib>

namespace in_game_objects {

  const int START_LEVEL = 1;
  const int NAMESTRING_SIZE = 30;
  const int DESCRSTRING_SIZE = 300;

  enum TClassId = { CI_GAME_OBJECT, CI_STATIC_GAME_OBJECT, CI_ALIVE_GAME_OBJECT, CI_PARTY_MEMBER, CI_PLAYER, CI_HENCHMEN, CI_MONSTER, CI_QUEST_MONSTER, CI_COMMON_MONSTER, CI_GRUNT_MONSTER, CI_DAMAGER_MONSTER, CI_SUPPORT_MONSTER };

  class GameObject {
    public:
      GameObject();
      GameObject(int level);
      virtual ~GameObject()
      int get_id();
      int get_own_id();
      int get_level();
      char* get_name();
      virtual in_game_objects::TClassId get_class();

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
	  virtual in_game_objects::TClassId get_class();
	  char* get_description()
    protected:    
      char* _description;
  };

  class Item: public StaticGameObject {
    public:
      Item();
      virtual ~Item();
      virtual in_game_objects::TClassId get_class();
      int get_cost();
    protected:
      _cost: int;
  };

  class EquipableItem: public Item {
    public:
      EquipableItem();
      virtual ~EquipableItem();
      virtual in_game_objects::TClassId get_class();
      int get_req_level();
      int* get_req_stats();
      int* get_bon_stats();
    protected:
      int _req_level;
      int* _req_stats;
      int* _bon_stats;
  };


  class AliveGameObject: public GameObject {
    public:

    protected:
      int* _health;
      int* _coords;
      int* _exp;
  };
  
}
