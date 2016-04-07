#include "QuestItem.h"

  QuestItem::QuestItem(TCollectablePrototype &prototype): CollectableItem() {
    _name = new char[NAMESTRING_SIZE];
    _description = new char[DESCRSTRING_SIZE];
    for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
      _name[i] = prototype._name[i];
	}
	for (size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
      _description[i] = prototype._description[i];
	}
	_quest_id = prototype._id;
	_cost = prototype._cost;
  }
  
  QuestItem::~QuestItem() {
  }
  
  int QuestItem::get_quest_id() {
    return _quest_id;
  }
