#ifndef MOVE_H
#define MOVE_H

#include "Action.h"
#include "Battlefield.h"

class Move: public Action {
  public:
    Move(AliveGameObject* sender, bool is_forward);
    virtual ~Move();
    
	AliveGameObject* get_sender();
    void set_sender(AliveGameObject* value);
    
    int implement();
  protected:
  	AliveGameObject* _sender;
  	bool is_forward;
};

#endif
