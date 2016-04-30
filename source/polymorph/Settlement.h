#include "Location.h"

class Settlement: Location {
  public:
  	Settlement();
  	virtual ~Settlement();
  	
  	int entrance();
  	
  	Trader** _traders;
  	Henchman** _mercs;
  	
  protected:
    int generate_traders();
    int generate_mercenaries();
};
