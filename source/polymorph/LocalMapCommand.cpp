#include "LocalMapCommand.h"

LocalMapCommand::LocalMapCommand(int sender_x_coord, int sender_y_coord, int target_x_coord,int target_y_coords): BackendCommand() {
  get_object_by_coord(sender_x_coord, sender_y_coord, _sender);
  get_object_by_coord(target_x_coord, target_y_coord, _target);
}

int LocalMapCommand::get_object_by_coords(int x_coord, int y_coord, GameObject* &object) {

  return 0;
}
