#include "Move.h"

Move::Move(Battlefield* battlefield, int sender_x_coord, int sender_y_coord, int target_x_coord, int target_y_coord): Action() {
  _battlefield = battlefield;
  _sender = new int[PAIR_ARR_SIZE] {sender_x_coord, sender_y_coord};
  _target = new int[PAIR_ARR_SIZE] {target_x_coord, target_y_coord};
}

Move::~Move() {
  delete[] _sender;
  delete[] _target;
}

int* Move::get_sender() {
  if (_sender != NULL) {
    int* result = new int[PAIR_ARR_SIZE] {_sender[0], _sender[1]};
    return result;
  } else {
    return NULL;
  }
}

AliveGameObject* Move::get_sender() {
  if (_sender != NULL && _battlefield != NULL) {
    return _battlefield->_map->_map[_sender[0]][_sender[1]]->_on_tile;
  } else {
    return NULL;
  }
}

void  Move::set_sender(int* value) {
  if (value != NULL) {
    for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
      _sender[i] = value[i];
	}
  }
}

int* Move::get_target() {
  if (_target != NULL) {
    int* result = new int[PAIR_ARR_SIZE] {_target[0], _target[1]};
    return result;
  } else {
    return NULL;
  }
}

AliveGameObject* Move::get_target() {
  if (_target != NULL && _battlefield != NULL) {
    return _battlefield->_map->_map[_target[0]][_target[1]]->_on_tile;
  } else {
    return NULL;
  }
}

void Move::set_target(int* value) {
  if (value != NULL) {
    for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
      _target[i] = value[i];
	}
  }
  return 0;
}

int Move::implement() {
  int* sender_health = _sender->get_health();
  if (sender_health[CURRENT_VALUE_INDEX] <= 0) {
    return 0;
  }
  delete[] sender_health;
  if (_battlefield->_map->_map[_target[0]][_target[1]]->get_is_passbale() && _battlefield->_map->_map->_on_tile == NULL) {
    _battlefield->_map->_map[_target[0]][_target[1]]->_on_tile = _battlefield->_map->_map[_sender[0]][_sender[1]]->_on_tile;
    _battlefield->_map->_map[_sender[0]][_sender[1]]->_on_tile = NULL;
  }
  //place frontend comand here
  return 0;
}
