#include "NextLocationCommand.h"

int NextLocationCommand::execute() {
  if (_world != NULL) {
    if (_world->_battlefield != NULL) {
      bool is_end;
      bool is_victory;
      _world->_battlefield->if_end_fight(is_victory, is_end);
      if (!is_end) {
      	return 0;
	  } else {
        if (is_victory) {
          delete _world->_battlefield;
		} else {
          //game over comand here;
		}
	  }
	}
	delete _world->_current_location;
	Forge* forge = new Forge("classic2.db");
	int response = forge->MakeLocation(rand() % LOCATION_PRESETS_COUNT + 1,_world->_player->get_average_level(), &(_world->_current_location));
	_world->_current_location->entrance();
	delete forge;
  }
  return 0;
}
