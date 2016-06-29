#include "CollectableItem.h"

#pragma once

  class QuestItem: public CollectableItem {
    public:
      QuestItem(TCollectablePrototype &prototype) : CollectableItem() {}
      virtual ~QuestItem() {}
      int get_quest_id() { return _quest_id; }
      int get_pic_name(std::string &out) { return 0; }
    protected:
      int _quest_id; //change to Quest* after Quest class development
  };

