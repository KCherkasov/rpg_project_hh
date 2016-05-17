#include "Attack.h"

Attack::Attack(Battlefield* battlefield, int sender_x_coord, int sender_y_coord, int target_x_coord, int target_y_coord): Action(){
  _battlefield = battlefield;
  _distance = count_distance(sender_x_coord, sender_y_coord, target_x_coord, target_y_coord);
  _sender = NULL;
  _target = NULL;
  get_object_by_coord(sender_x_coord, sender_y_coord, _sender);
  get_object_by_coord(target_x_coord, target_y_coord, _target)
}

Attack::~Attack() {
  _sender = NULL;
  _target = NULL;
}

int Attack::implement() {
  if (_sender != NULL && _target != NULL) {
  	srand(static_cast<unsigned int>(time(0)));
    int result;
    int* sender_health = _sender->get_health();
    int* target_health = _target->get_health();
    if (target_health[CURRENT_VALUE_INDEX] <= 0 || sender_health[CURRENT_VALUE_INDEX] <= 0) {
      return 0;
	}
	delete[] sender_health;
	delete[] target_health;
	if (_distance <= _sender->get_range()) {
      if (_sender->make_hit_roll(_distance)) {
        int damage = _sender->count_extra_damage(_sender->count_damage());
        _target->set_health(FREE_INDEX * damage);
	  }
	}
  }
  return 0;
}

AliveGameObject* Attack::get_sender() {
  return _sender;
}

AliveGameObject* Attack::get_target() {
  return _target;
}

void Attack::set_sender(AliveGameObject* value) {
  	_sender = value;
}

void Attack::set_target(AliveGameObject* value) {
  _target = value;
}

int Attack::count_distance(int x1_coord, int y1_coord, int x2_coord, int y2_coord) {
  int distance = 0;
  if (x1_coord >= x2_coord) {
    distance += x1_coord;
    distance -= x2_coord;
  } else {
    distance += x2_coord;
    distance -= x1_coord;
  }
  if (y1_coord >= y2_coord) {
    distance += y1_coord;
    distance -= y2_coord;
  } else {
    distance += y2_coord;
    distance -= y1_coord;
  }
  return distance;
}
