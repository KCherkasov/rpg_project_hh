#ifndef LOCAL_MAP_COMMAND_H
#define LOCAL_MAP_COMMAND_H

#include "BackendCommand.h"
#include "LocalMap.h"
#include "Battlefield.h"
#include "PartyMember.h"
#include "GruntMonster.h"
#include "DamagerMonster.h"
#include "SupportMonster.h"
#include "CommonMonster.h"
#include "QuestMonster.h"
#include "Attack.h"
#include "Move.h"
#include "prototypes.h"

class LocalMapCommand: public BackendCommand {
  public:
    LocalMapCommand(Battlefield* battlefield, int sender_x_coord, int sender_y_coord, int target_x_coord, int target_y_coord);
    virtual ~LocalMapCommand();
    int add_into_queue();
    int add_frontend_callback(/*place here code to transfer frontend command into query*/);
	int execute();
  protected:
    int* _sender;
	int* _target;
	Battlefield* _battlefield;
};

#endif
