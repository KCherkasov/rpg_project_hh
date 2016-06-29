#include "prototypes.h"
#include <string>

#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

using namespace generic_consts;
using namespace prototypes;

class GameObject {
    public:
      GameObject() { _own_id = 0; _pic_id = 0; _level = START_LEVEL; _name = NULL; }
      GameObject(int level) { _own_id = 0; _pic_id = 0; _level = level; _name = NULL; }
      virtual ~GameObject() { delete[] _name; }
      int get_own_id() { return _own_id; }
      int get_level() { return _level; }
      unsigned char* get_name() { return _name; }
      virtual int what(std::string &out) { return 0; }
      virtual int get_pic_name(std::string &out) { return 0; }

    protected:
      int _own_id;
      int _pic_id;
      int _level;
      unsigned char* _name;
};

#endif
