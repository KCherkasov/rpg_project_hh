#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include "WeaponTrader.h"
#include "ArmourTrader.h"
#include "MunitionsTrader.h"
#include "BlackMarket.h"
#include "PartyMember.h"
#include "Location.h"
#include "Forge.h"

#include <cmath>
#include <ctime>
#include <cstdlib>

class Settlement: Location {
  public:
  	Settlement(TLocationPrototype prototype, int level);
  	virtual ~Settlement();
  	
  	int entrance();
  	
  	Trader** _traders;
  	PartyMember** _mercs;
  	
  protected:
    int generate_traders();
    int generate_mercenaries();
};

#endif
