#include "Trader.h"
#include "Forge.h"
#include "Item.h"
#include <cstdlib>
#include <ctime>

#pragma once

class MunitionsTrader: Trader {
  public:
    MunitionsTrader(): Trader() {}
    MunitionsTrader(TNPCPrototype &prototype, int level);
    virtual ~MunitionsTrader();
    
    Item** _assortment;

  protected:
  	int form_assortment(TNPCPrototype &prototype, int level);
};
