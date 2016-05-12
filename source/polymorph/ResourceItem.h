#include "CollectableItem.h"

#pragma once

  class ResourceItem: public CollectableItem {
    public:
      ResourceItem(TCollectablePrototype &prototype);
      virtual ~ResourceItem();
      int get_resource_id();
      int get_pic_name(std::string &out);
    protected:
      int _resource_id;
  };

