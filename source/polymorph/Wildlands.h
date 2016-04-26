#include "Location.h"
#include "CollectableItem.h"

class Wildlands: public Location {
  public:
  	Wildlands();
  	virtual ~Wildlands();
  	
  	int entrance();
  	int generate_battlefield(); //re-set signature later;
  	
  	int** _enemies;
	CollectableItem** _loot;
};
