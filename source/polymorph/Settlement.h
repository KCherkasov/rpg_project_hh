#include "Location.h"

class Settlement: Location {
  public:
  	Settlement();
  	virtual ~Settlement();
  	
  	int entrance();
  	
  	Trader** _traders;
  	Henchman** _mercs;
};
