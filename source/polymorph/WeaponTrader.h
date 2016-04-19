#include "Trader.h"
#include "Weapon.h"

class WeaponTrader {
  public:
    WeaponTrader()
    WeaponTrader(TNPCPrototype &prototype, int level);
    virtual ~WeaponTrader();
    
    Weapon** _assortment;
    
  protected:
    int form_assortment(TNPCPrototype &prototype, int level);
};
