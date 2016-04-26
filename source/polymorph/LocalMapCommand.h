#include "BackendCommand.h"

class LocalMapCommand: public BackendCommand {
  public:
    LocalMapCommand(int sender_x_coord, int sender_y_coord, int target_x_coord, int target_y_coord); //place here code to extract GameObject from local map coordinates
    LocalMapCommand(GameObject** sender, GameObject** target): BackendCommand(sender, target) {}//for direct access to game object
  protected:
  	int get_object_by_coords(int x_coord, int y_coord, GameObject* &object);
};
