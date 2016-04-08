#include "Item.h"

#pragma once

  class UsableItem: public Item {
    public:
      UsableItem();
      virtual ~UsableItem();
      TItemRareness get_rarity();
    protected:
      TItemRareness _rarity;
  };
