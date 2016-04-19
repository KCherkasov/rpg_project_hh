#include "Trader.h"
#include "Armour.h"

class ArmourTrader: Trader {
  public:
    ArmourTrader(): Trader() {}
    ArmourTrader(TNPCPrototype &prototype, int level);
    virtual ~ArmourTrader();
    
    Armour** _assortment;

  protected:
  	int form_assortment(TNPCPrototype &prototype, int level);
};
