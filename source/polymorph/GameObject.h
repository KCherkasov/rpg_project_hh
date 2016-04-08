#include "prototypes.h"
#include <string>

#pragma once

using namespace generic_consts;
using namespace prototypes;

class GameObject {
    public:
      GameObject();
      GameObject(int level);
      virtual ~GameObject();
      int get_own_id();
      int get_level();
      unsigned char* get_name();
      virtual char* what() = 0;

    protected:
      int _own_id;
      int _level;
      unsigned char* _name;
};
