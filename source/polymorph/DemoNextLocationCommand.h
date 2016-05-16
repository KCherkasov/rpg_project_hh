#ifndef  DEMO_NEXT_LOCATION_COMMAND_H
#define DEMO_NEXT_LOCATION_COMMAND_H

#include "World.h"
#include "BackendCommand.h"

class DemoNextLocationCommand: public BackendCommand {
  public:
    DemoNextLocationCommand(World* &world): BackendCommand() { _world = world; }
    virtual ~DemoNextLocationCommand() { _world = NULL; }
    int execute();
  protected:
    World* _world;
};

// Note: this command written only for battle system testing purposes
// this command differs from NextLocationCommand in spawning logic: 
// demo command always spawns battles, without looking at if_fight() Location method's result

#endif
