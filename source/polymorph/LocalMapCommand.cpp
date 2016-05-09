#include "LocalMapCommand.h"

LocalMapCommand::LocalMapCommand(Battlefield* battlefield, int sender_x_coord, int sender_y_coord, int target_x_coord,int target_y_coords): BackendCommand() {
  _sender = new int[PAIR_ARR_SIZE] {sender_x_coord, sender_y_coord};
  _target = new int[PAIR_ARR_SIZE] {target_x_coord, target_y_coord};
  _battlefield = battlefield;
}

LocalMapCommand::~LocalMapCommand() {
  delete[] _sender;
  delete[] _target;
  _battlefield = NULL;
}

int LocalMapCommand::add_into_queue() {
  if (_battlefield->_map->_map[_target[0]][_target[1]]->_on_tile == NULL) {
    for(size_t i = 0; i <  (ACTIONS_PER_TURN * (PLAYER_SQUAD_SIZE + MAX_MONSTER_SQUADS * MONSTER_SQUAD_SIZE)); ++i) {
      if (_battlefield->_turn_queue[i] == NULL) {
        _battlefield->_turn_queue[i] = new Move(_battlefield, _sender[0], _sender[1], _target[0], _target[1]);
	  }
	}
  } else {
    for(size_t i = 0; i <  (ACTIONS_PER_TURN * (PLAYER_SQUAD_SIZE + MAX_MONSTER_SQUADS * MONSTER_SQUAD_SIZE)); ++i) {
      if (_battlefield->_turn_queue[i] == NULL) {
        _battlefield->_turn_queue[i] = new Attack(_battlefield, _sender[0], _sender[1], _target[0], _target[1]);
	  }
	}
  }
  return 0;
}

int LocalMapCommand::add_frontend_callback(/*argument where to place frontend command there*/) {
  return 0;
}

int LocalMapCommand::execute() {
  return add_into_queue();
}
