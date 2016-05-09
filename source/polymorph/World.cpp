#include "World.h"

World::World() {
  _player = new Player();
  _battlefield = NULL;
  _location = NULL;
  _backend_query.clear();
  //_input_query.clear();
  //_output_query.clear();
}

World::~World {
  delete _player;
  delete _battlefield;
  delete _location;
  for (size_t i = 0; i < _backend_query.size(); ++i) {
    if (_backend_query[i] != NULL) {
      delete _backend_query[i];
	}
  }
  /*for (size_t i = 0; i < _backend_query.size(); ++i) {
    if (_input_query[i] != NULL) {
      delete _input_query[i];
	}
  }*/
  /*for (size_t i = 0; i < _backend_query.size(); ++i) {
    if (_output_query[i] != NULL) {
      delete _input_query[i];
	}
  }*/
}

int World::render() {
  // add some 
  return 0;
}
