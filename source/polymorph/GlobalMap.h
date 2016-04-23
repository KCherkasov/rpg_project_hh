#ifndef GLOBALMAP_H
#define GLOBALMAP_H

#include "prototypes.h"
#include "LocalMapObject.h"

const int GLOBAL_MAP_WIDTH = 300;
const int GLOBAL_MAP_HEIGHT = 300;

class GlobalMap {
  public: 
    GlobalMap();
    GlobalMap(LocalMapObject*** &source);
    ~GlobalMap();
    
    LocalMapObject*** _map;
};

#endif
