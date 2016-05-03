#include "Battlefield.h"

Battlefield::Battlefield() {
  _map = NULL;
  _stash = NULL;
}

Battlefield::~Battlefield() {
  delete _map;
  delete _stash;
}
