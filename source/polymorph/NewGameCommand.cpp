#include "NewGameCommand.h"

NewGameCommand::NewGameCommand(World* world, char* &name): BackendCommand() {
  _world = world;
  _player_squad_name = new char[NAMESTRING_SIZE] {};
  if (name != NULL) {
    for (size_t i = 0; i < NAMESTRING_SIZE && name[i] != '\0'; ++i) {
      _player_squad_name[i] = name[i];
    }
  }
  delete[] name;
}

NewGameCommand::~NewGameCommand() {
  _world = NULL;
  delete[] _player_squad_name;
}

int NewGameCommand::execute() {
  if (_world == NULL) {
    _world = new World(_player_squad_name);
  }
  return 0;
}
