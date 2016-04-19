#include "StaticGameObject.h"
#include "AliveGameObject.h"
#include "prototypes. h"

class LocalMapObject: StaticGameObject {
  public:
  	LocalMapObject();
  	LocalMapObject(TTilePrototype &prototype);
  	virtual ~LocalMapObject();

  	int get_texture_id() { return _texture_id; }
  	int get_defense() { return _defense; }
  	bool get_is_passable { return _is_passable; }
	
  	AliveGameObject* _on_tile;
  	
  protected:
    int _texture_id;
    int _defense;
    bool _is_passable;
};
