#include "Item.h"

#pragma once

  class UsableItem: public Item {
    public:
      UsableItem();
      virtual ~UsableItem();
      TItemRareness get_rarity();
      virtual int use() = 0;
    protected:
      TItemRareness _rarity;
  };
