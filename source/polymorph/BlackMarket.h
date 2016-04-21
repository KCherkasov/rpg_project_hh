#include "Trader.h"
#include "Forge.h"
#include "Item.h"
#include <cstdlib>
#include <ctime>

#pragma once

class BlackMarket: Trader {
  public:
    BlackMarket();
    BlackMarket(TNPCPrototype &prototype, int level);
    virtual ~BlackMarket();
    
    Item** _assortment;
    
  protected:
    int form_assortment(TNPCPrototype &prototype, int level);
};
