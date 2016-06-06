#ifndef MOVE_H
#define MOVE_H

#include "Action.h"
#include "Battlefield.h"

class Move: public Action {
  public:
    Move(Battlefield* battlefield, int sender_x_coord, int sender_y_coord, int target_x_coord, int target_y_coord);
    virtual ~Move();
    
    int* get_sender_coords();
    AliveGameObject* get_sender();
    void set_sender(int* value);
    int* get_target_coords();
    AliveGameObject* get_target();
    void set_target(int* value);
    
    int implement();
  protected:
  	Battlefield* _battlefield;
  	int* _sender;
  	int* _target;
};

#endif
