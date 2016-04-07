#include "CollectableItem.h"

#pragma once

  class QuestItem: public CollectableItem {
    public:
      QuestItem(TCollectablePrototype &prototype);
      virtual ~QuestItem();
      int get_quest_id();
    protected:
      int _quest_id; //change to Quest* after Quest class development
  };

