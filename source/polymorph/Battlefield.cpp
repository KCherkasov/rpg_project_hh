#include "Battlefield.h"

Battlefield::Battlefield() {
  _map = NULL;
  _stash = NULL;
  _player = NULL;
  _squads = NULL;
  _turn_queue = NULL;
  _turn_no = 0;
}

Battlefield::Battlefield(Location* location, Player* &player) {
  if (location != NULL) {
  	_map = NULL;
    _player = player;
  	_stash = NULL;
  	_squads = new Squad*[MAX_MONSTER_SQUADS] {NULL};
  	_turn_queue =new Action*[ACTIONS_PER_TURN * (MONSTER_SQUAD_SIZE * MAX_MONSTER_SQUADS + PLAYER_SQUAD_SIZE)] {NULL};
    int fact_level; 
	location->count_fact_level(fact_level);
	srand(static_cast<unsigned int>(time(0)));
	for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
      int rnd = rand() % PERCENT_MOD_CAP + 1;
      int *pack_data = NULL;
      location->get_pack_info(pack_data, i);
      if (rnd <= pack_data[1]) {
        int null_squad = FREE_INDEX;
        for (size_t j = 0; j < MAX_MONSTER_SQUADS; ++j) {
          if (_squads[j] == NULL) {
            null_squad = j;
            break;
		  }
		}
        _squads[null_squad] = new Squad(null_squad + 1, MONSTER_SQUAD_SIZE);
        spawn_new_pack(pack_data[0], false, fact_level, _squads[null_squad]->get_pack_id());
	  }
	}
  }
}

Battlefield::~Battlefield() {
  delete _map;
  delete _stash;
  _player = NULL;
  for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    delete _squads[i];
  }
  for (size_t i = 0; i < ACTIONS_PER_TURN * (MONSTER_SQUAD_SIZE * MAX_MONSTER_SQUADS + PLAYER_SQUAD_SIZE); ++i) {
    if (_turn_queue[i] != NULL) {
      delete _turn_queue[i];
	}
  }
  delete[] _turn_queue;
  delete[] _squads;
}

int Battlefield::spawn_new_pack(int monster_id, bool target_there, int level, int squad_id) {
  int response;
  srand(static_cast<unsigned int>(time(0)));
  if (squad_id > PLAYER_SQUAD_ID && squad_id < (MAX_MONSTER_SQUADS + 1)) {
    Forge* forge = new Forge("classic2.db");
    int rnd;
    int spawned = 0;
    for (size_t i = 0; i < MONSTER_SQUAD_SIZE; ++i) {
      rnd = rand() % PERCENT_MOD_CAP;
      if (rnd <= (PERCENT_MOD_CAP - spawned * SPAWN_CHANCE_DECREMENT)) {
      	delete _squads[squad_id - 1]->_members[spawned];
      	response = forge->MakeMonster(monster_id, level, &(_squads[squad_id - 1]->_members[spawned]));
      	++spawned;
	  } else {
        break;
	  }
	}
    delete forge;
  }
  return response;
}

int Battlefield::pack_set_leader(int pack_id) {
  if (pack_id > FREE_INDEX && pack_id < MAX_MONSTER_SQUADS) {
    if (_squads[pack_id] != NULL) {
      for (size_t i = 0; i < MONSTER_SQUAD_SIZE; ++i) {
        if (_squads[pack_id]->_members[i] != NULL && !_squads[pack_id]->_members[i]->get_is_leader()) {
          _squads[pack_id]->_members[i]->try_make_leader();
		}
	  }
	}
  }
  return 0;
}

int Battlefield::set_mass_leader() {
  for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
  	bool already_spawned;
  	mass_leader_is_spawned(already_spawned);
  	if (already_spawned) {
      break;
    }
    if (_squads[i] != NULL) {
      int leader_index;
      pack_has_leader(i, leader_index);
      if (leader_index > FREE_INDEX) {
        _squads[i]->_members[leader_index]->try_make_mass_leader();
	  }
	}
  }
  return 0;
}

int Battlefield::pack_has_leader(int pack_id, int &result_index) {
  result_index = FREE_INDEX;
  if (pack_id > FREE_INDEX && pack_id < MAX_MONSTER_SQUADS) {
    if (_squads[pack_id] != NULL) {
      for (size_t i = 0; i < MONSTER_SQUAD_SIZE; ++i) {
        if (_squads[pack_id]->_members[i] != NULL) {
          if (_squads[pack_id]->_members[i]->get_is_leader()) {
            result_index = i;
            break;
		  }
		}
	  }
	}
  }
  return 0;
}

int Battlefield::mass_leader_is_spawned(bool &result) {
  result = false;
  for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    if (_squads[i] != NULL) {
      for (size_t j = 0; j < MONSTER_SQUAD_SIZE; ++j) {
        if (_squads[i]->_members[j] != NULL) {
          result = _squads[i]->_members[j]->get_is_mass_leader();
		}
		if (result) {
          break;
		}
	  }
	  if (result) {
        break;
	  }
	}
  }
  return 0;
}

int Battlefield::place_units_on_map() {
  for (size_t i = 0; i < PLAYER_SQUAD_SIZE; ++i) {
    if (_player->_squad->_members[i] != NULL) {
      while (true) {
        int x_coord = rand() % LOCAL_MAP_HEIGHT;
        int y_coord = rand() % (LOCAL_MAP_WIDTH / 8);
        if (_map->_map[x_coord][y_coord]->_on_tile == NULL) {
          _map->_map[x_coord][y_coord]->_on_tile = _player->_squad->_members[i];
          break;
		}
	  }
	}
  }
  for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    if (_squads[i] != NULL) {
      for (size_t j = 0; j < MONSTER_SQUAD_SIZE; ++j) {
        if (_squads[i]->_members[j] != NULL) {
          while (true) {
            int x_coord = rand() % LOCAL_MAP_HEIGHT;
            int y_coord = LOCAL_MAP_WIDTH / 8 * 7 + rand() % (LOCAL_MAP_WIDTH / 8);
            if (_map->_map[x_coord][y_coord]->_on_tile == NULL) {
              _map->_map[x_coord][y_coord]->_on_tile = _squads[i]->_members[j];
			}
		  }
		}
	  }
	}
  }
  return 0;
}

int Battlefield::make_turn() {
  ++_turn_no;
  sort_turn_queue;
  for (size_t i = 0; i < (ACTIONS_PER_TURN * (PLAYER_SQUAD_SIZE + MAX_MONSTER_SQUADS * MONSTER_SQUAD_SIZE)); ++i) {
    _turn_queue[i]->implement();
    delete _turn_queue[i];
  }
  clear_dead();
  return 0;
}

int Battlefield::if_end_fight(bool &is_victory, bool &is_end) {
  is_victory = true;
  is_end = false;
  int player_alive = 0;
  _player->_squad->count_alive(player_alive);
  if (player_alive == 0) {
  	is_victory = false;
  	is_end = true;
  } else {
  	int sum_enemies_alive = 0;
  	for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
      if (_squads[i] != NULL) {
        int squad_alive = 0;
        _squads[i]->count_alive(squad_alive);
        sum_enemies_alive += squad_alive;
	  }
    }
    if (sum_enemies_alive == 0) {
      is_end = true;
      is_victory = true;
	}
  }
  return 0;
}

int Battlefield::clear_dead() {
  for (size_t i = 0; i <  PLAYER_SQUAD_SIZE; ++i) {
    if (_player->_squad->_members[i] != NULL) {
      int* health = _player->_squad->_members[i]->get_health();
      if (health[CURRENT_VALUE_INDEX] <= 0) {
        _player->change_cash(FREE_INDEX * CRITICAL_HIT_MODIFIER * _player->_squad->_members[i]->get_salary());
        for (size_t j = 0; j < ES_SIZE; ++i) {
          _stash->_stash.push_back(_player->_squad->_members[i]->_equipped->_content[j]);
	    }
        delete _player->_squad->_members[i];
      }
      delete[] health;
    }
  }
  for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    for (size_t j = 0; j < MONSTER_SQUAD_SIZE; ++j) {
      if (_squads[i]->_members[j] != NULL) {
        int* health = _squads[i]->_members[j]->get_health();
        if (health[CURRENT_VALUE_INDEX] <= 0) {
          _squads[i]->_members[j]->generate_loot(_stash);
          delete _squads[i]->_members[j];
		}
        delete[] health;
	  }
	}
  }
  return 0;
}

int Battlefield::sort_turn_queue() {
  for (size_t i = 0; i < (ACTIONS_PER_TURN * (PLAYER_SQUAD_SIZE + MAX_MONSTER_SQUADS * MONSTER_SQUAD_SIZE)) - 1; ++i) {
  	int max_index = i;
    for (size_t j = i+1; j < (ACTIONS_PER_TURN * (PLAYER_SQUAD_SIZE + MAX_MONSTER_SQUADS * MONSTER_SQUAD_SIZE)); ++j) {
      if (_turn_queue[max_index] == NULL) {
      	max_index = j;
	  } else {
	    if (_turn_queue[j] != NULL) {
          AliveGameObject* max_sender = _turn_queue[max_index]->get_sender();
          AliveGameObject* j_sender = _turn_queue[j]->get_sender();
          if (max_sender->get_initiative() < j_sender->get_initiative()) {
            max_index = j;
	      }
          max_sender = NULL;
          j_sender = NULL;
	    }
      }
	}
	Action* tmp = _turn_queue[max_index];
	_turn_queue[max_index] = _turn_queue[i];
	_turn_queue[i] = tmp;
	tmp = NULL;
  }
  return 0;
}
