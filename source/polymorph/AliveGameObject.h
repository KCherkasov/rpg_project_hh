#ifndef ALIVEGAMEOBJECT_H
#define ALIVEGAMEOBJECT_H

#include "GameObject.h"
#include "Inventory.h"
#include "Storage.h"
#include "Equipped.h"
#include "prototypes.h"

#pragma once

  class AliveGameObject: public GameObject {
    public:
      AliveGameObject();
      virtual ~AliveGameObject();
      int* get_health();
      int* get_exp();
      int get_stat(int index, int &result);
      int* get_stats();
      
      Inventory* _bag;
      Inventory* _equipped;
      
    protected:
      int* _health;
      int* _exp;
      int* _stats;
  };

#endif
