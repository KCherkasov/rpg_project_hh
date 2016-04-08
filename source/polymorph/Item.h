#include "StaticGameObject.h"

#pragma once

using namespace generic_consts;
using namespace prototypes;

  class Item: public StaticGameObject {
    public:
      Item();
      virtual ~Item();
      int get_cost();
      bool get_in_bag();
      virtual int use() { return 0; }
    protected:
      int _cost;
      bool _in_bag;
  };

