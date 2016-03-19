#include "in_game_objects.h"      
      
  in_game_objects::GameObject::GameObject() : _own_id(++_id), _level(START_LEVEL), _name(NULL) {}

  in_game_objects::GameObject::GameObject(int inp_level): _own_id(++id), _level(inp_level), _name(NULL) {}
  
  in_game_objects::GameObject::~GameObject() {
    delete[] _name;
  }

  int in_game_objects::GameObject::get_id() {
    return _id;
  }

  int in_game_objects::GameObject::get_own_id() {
    return _own_id;
  }

  int in_game_objects::GameObject::get_level() {
    return _level;
  }

  char* in_game_objects::GameObject::get_name() {
    if (_name == NULL) { 
      char* res = _name; 
    } else {
      char* res = new char[NAMESTRING_SIZE];
      for (int i = 0; i < NAMESTRING_SIZE; ++i) {
        res[i] = _name[i];
      }
    }
    return res;
  }

  in_game_objects::TClassId in_game_objects::GameObject::get_class() {
    return CI_GAME_OBJECT;
  }

  in_game_objects::StaticGameObject::StaticGameObject() : GameObject()  {
    _description = NULL;
  }

  in_game_objects::StaticGameObject::~StaticGameObject() {
  	delete[] _description;
  }

  in_game_objects::TClassId in_game_objects::StaticGameObject::get_class() {
    return CI_STATIC_GAME_OBJECTS;
  }

  char* in_game_objects::StaticGameObject::get_description() {
    if (_description == NULL) {
      return _description;
	} else {
      char* res = new char[DESCRSTRING_SIZE];
      for (int i = 0; i < DESCRSTRING_SIZE; ++i) {
        res[i] = _description[i];
	  }
	  return res;
	}
  }

  in_game_object::Item::Item() : StaticGameObject() {
    _cost = 0;
  }

  in_game_object::Item::~Item() {
  }

  in_game_object::TClassId in_game_object::Item::get_class() {
    return CI_ITEM;
  }

  int in_game_object::Item::get_cost() {
    return _cost;
  } 

  in_game_objects:: EquipableItem() : Item() {
    
  }
