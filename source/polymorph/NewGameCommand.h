#ifndef NEW_GAME_COMMAND_H
#define NEW_GAME_COMMAND_H

#include "BackendCommand.h"
#include "World.h"

class NewGameCommand: public BackendCommand {
  public:
    NewGameCommand(World* world, char* &name);
    virtual NewGameCommand();
    int execute();
  protected:
    World* _world;
	char* _player_squad_name;
    // int _player_pic_id;
};

#endif
