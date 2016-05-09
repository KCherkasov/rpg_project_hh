#ifndef ACTION_H
#define ACTION_H

#include "prototypes.h"
#include "LocalMap.h"
#include "Battlefield.h"
#include "PartyMember.h"
#include "GruntMonster.h"
#include "DamagerMonster.h"
#include "SupportMonster.h"
#include "CommonMonster.h"
#include "LocalMapObject.h"
#include "Monster.h"

class Action {
  public:
  	Action() { _battlefield = NULL; }
  	virtual ~Action() { _battlefield = NULL; }
    virtual int implement() = 0;
  protected: 
    int get_object_by_coord(int x_coord, int y_coord, AliveGameObject* &result);
    Battlefield* _battlefield;
};

#endif
