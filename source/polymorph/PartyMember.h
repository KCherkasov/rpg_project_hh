#ifndef PARTYMEMBER_H
#define PARTYMEMBER_H

#include "AliveGameObject.h"
#include "prototype.h"

class PartyMember: public AliveGameObject {
  public:
  	PartyMember();
  	virtual ~PartyMember();
    int get_stat(int index, int &result);
    int* get_stats();
  	
  	Inventory* _bag;
  	Inventory* _equipped;
  protected:
  	
    int* _stats;
    int _killed_count;
    int _money_earned;
    
};

#endif
