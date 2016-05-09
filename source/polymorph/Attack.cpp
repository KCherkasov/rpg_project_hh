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
	_battlefield->_player->_squad->get_member_index(_sender, result);
	if (result != FREE_INDEX) {
      //if attacker is a party member
      if (_distance <= _sender->_equipped->_content[ES_WEAPON1]->get_distance()) {
        int hit_chance = PERCENT_MOD_CAP / 2;
        int accuracy; 
		_sender->get_stat(CS_ACCURACY, accuracy);
        hit_chance -= distance;
        hit_chance += accuracy / 5;
        if (hit_chance < 0) {
          hit_chance = 1;
		}
		if(hit_chance > PERCENT_MOD_CAP) {
          hit_chance = PERCENT_MOD_CAP;
		}
		int dice_roll = rand() % PERCENT_MOD_CAP;
		if (dice_roll <= hit_chance) {
          int* damage = _sender->_equipped->_content[ES_WEAPON1]->get_damage();
          int total_damage = rand() % (damage[1] - damage[0]) + damage[0] + 1;
          if (_sender->_equipped->_content[ES_WEAPON2] != NULL) {
            if (distance <= _sender->_equipped->_content[ES_WEAPON2]->get_distance()) {
              delete[] damage;
              damage = _sender->_equipped->_content[ES_WEAPON2]->get_damage();
              int extra_damage = rand() % (damage[1] - damage[0]) + damage[0] + 1;
              total_damage += extra_damage;
			}
		  }
          int critical_hit_roll = rand() % PERCENT_MOD_CAP;
          if (critical_hit <= BASE_CRITICAL_HIT_CHANCE) {
          	total_damage *= CRITICAL_DAMAGE_MODIFIER;
		  }
		  delete[] damage;
		  total_damage -= _target->_on_tile->get_defense();
		  _target->set_health(FREE_INDEX * total_damage);
		  int* rest_health = _target->get_health();
		  if (rest_health[CURRENT_VALUE_INDEX] <= 0) {
            //unit on-die code here:  place a command to frontend here
		    _sender->change_killed_count();
		  }
		  delete[] rest_health;
		}
	  }
	} else {
      //if attacker is a monster
      if (distance <= _sender->get_range()) {
        int hit_roll = rand() % PERCENT_MOD_CAP;
        int hit_chance = PERCENT_MOD_CAP / 2 - distance + rand() % (PERCENT_MOD_CAP / 5);
        if (hit_roll <= hit_chance) {
          int* damage = _sender->get_damage();
          int total_damage = damage[0] + 1 + rand() % (damage[1] - damage[0]);
          delete[] damage;
          total_damage -= _target->_equipped->get_defense();
          if (total_damage < 0) {
            total_damage = 0;
		  }
		  int critical_roll = rand() % PERCENT_MOD_CAP;
		  if (critical_roll <= BASE_CRITICAL_HIT_CHANCE) {
            total_damage *= CRITICAL_HIT_MODIFIER;
		  }
		  _target->set_health(FREE_INDEX * total_damage);
		  int* rest_health = _target->get_health();
		  if (rest_health[CURRENT_VALUE_INDEX] <= 0) {
            //unit on-die code here: make a frontend comand and place in frontend query 
		  }
		  delete[] rest_health;
		}
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
