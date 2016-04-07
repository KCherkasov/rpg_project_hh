#include "GameObject.h"

#pragma once

using namespace generic_consts;
using namespace prototypes;

class StaticGameObject: public GameObject {
    public:
	  StaticGameObject();
	  virtual ~StaticGameObject();
	  unsigned char* get_description();
    protected:    
      unsigned char* _description;
  };
