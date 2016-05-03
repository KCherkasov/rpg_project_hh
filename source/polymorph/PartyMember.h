#ifndef PARTYMEMBER_H
#define PARTYMEMBER_H

#include "AliveGameObject.h"
#include "prototype.h"

class PartyMember: public AliveGameObject {
  public:
  	PartyMember();
  	virtual ~PartyMember();
  	
  	Inventory* _bag;
  	Inventory* _equipped;
  protected:
};

#endif
