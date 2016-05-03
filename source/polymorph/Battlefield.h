#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "LocalMap.h"
#include "Stash.h"

class Battlefield {
  public:
    Battlefield();
    Battlefield();
  	virtual ~Battlefield();
    LocalMap* _map;
    Stash* _stash;
};

#endif
