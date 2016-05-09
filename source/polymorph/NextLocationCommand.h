#ifndef NEXT_LOCATION_COMMAND_H
#define NEXT_LOCATION_COMMAND_H

#include"Location.h"
#include"Battlefield.h"
#include"World.h"
#inclue"BackendCommand.h"

#include <ctime>
#include <cmath>
#include <cstdlib>

class NextLocationCommand: public BackendCommand {
  public:
    NextLocationCommand(World* world): BackendCommand() { _world = world; }
    virtual ~NextLocationCommand() { _world = NULL; }
    int execute();
  protected:
  	World* _world;
};

#endif
