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
  	Action() {}
  	virtual ~Action() {}
    virtual int implement() = 0;
};

#endif
