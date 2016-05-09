#ifndef FIGHT_ENDTURN_COMMAND_H
#define FIGHT_ENDTURN_COMMAND_H

#include "BackendCommand.h"
#include "Battlefield.h"

class FightEndTurnCommand: public BackendCommand {
  public:
  	FightEndTurnCommand(Battlefield* battlefield): BackendCommand() { _battlefield = battlefield }
  	virtual ~FightEndTurnCommand() { _battlefield = NULL; }
  	int execute() { return _battlefield->make_turn(); }
  protected:
    Battlefield* _battlefield;
};

#endif
