#ifndef WILDLANDS_H
#define WILDLANDS_H

#include "Location.h"
#include "CollectableItem.h"

class Wildlands: public Location {
  public:
  	Wildlands() {}
  	virtual ~Wildlands() {}
  	
  	int entrance() { return 0; };
  	int generate_battlefield() { return 0; } 	
  	int** _enemies;
	CollectableItem** _loot;
};

#endif
