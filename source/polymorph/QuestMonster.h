#ifndef QUESTMONSTER_H
#define QUESTMONSTER_H

#include "Monster.h"

class QuestMonster: public Monster {
  public:
  	QuestMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level, int quest_id);
  	virtual ~QuestMonster();
    int decision(Battlefield* &battlefield);
  protected:
  	int _quest_id;
  	
    int evaluate(Battlefield* &battlefield, int &to_x, int &to_y, int &points);
};

#endif
