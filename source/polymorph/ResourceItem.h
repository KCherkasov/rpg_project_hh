#include "CollectableItem.h"

#pragma once

  class ResourceItem: public CollectableItem {
    public:
      ResourceItem(TCollectablePrototype &prototype);
      virtual ~ResourceItem();
      int get_resource_id();
    protected:
      int _resource_id;
  };

