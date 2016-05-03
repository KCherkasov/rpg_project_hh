#ifndef QUESTMONSTER_H
#define QUESTMONSTER_H

#include "Monster.h"

class QuestMonster: public Monster {
  public:
  	QuestMonster(TMonsterPrototype &prototype, int level, int quest_id);
  	virtual ~QuestMonster();
    int decision();
  protected:
  	int _quest_id;
  	
    int evaluate(int to_x, int to_y, int &points);
};

#endif
