#include "GameObject.h"
#include "Inventory.h"

#pragma once

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
