#include "Action.h"

int Action::get_object_by_coord(int x_coord, int y_coord, AliveGameObject* &result) {
  result = NULL;
  result = _battlefield->_map->_map[x_coord][y_coord]->_on_tile;
  return 0;
}
