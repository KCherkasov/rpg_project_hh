#include "LocalMapObject.h"

LocalMapObject::LocalMapObject(): StaticGameObject() {
  _texture_id = FREE_INDEX;
  _defense = 0;
  _is_passable = false;
}

LocalMapObject::LocalMapObject(TTilePrototype &prototype): StaticGameObject() {
  _texture_id = prototype._texture;
  _defense = prototype._defense;
  _is_passable = prototype._is_passable;
  _description = new unsigned char[DESCRSTRING_SIZE] {};
  _name = new unsigned char[NAMESTRING_SIZE] {};
  for (size_t i = 0; i < DESCRSTRING_SIZE && prototype._description[i] != '\0'; ++i) {
    _description[i] = prototype._description[i];
  }
  for (size_t i = 0; i < NAMESTRING_SIZE && prototype._name; ++i)
  delete[] prototype._description;
  delete[] prototype._name;
  _on_tile = NULL;
}

LocalMapObject::~LocalMapObject() { _on_tile = NULL; }


