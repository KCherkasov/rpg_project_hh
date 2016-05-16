#ifndef BUY_SELL_COMMAND_H
#define BUY_SELL_COMMAND_H

#include "World.h"
#include "BackendCommand.h"
#include "Player.h"

class BuySellCommand : public BackendCommand {
  public:
    BuySellCommand(World* &world, bool is_buying, int trader_id, int item_id);
    virtual ~BuySellCommand() { _world = NULL; }
    int execute();
  protected:
    World* _world;
    bool _is_buying;
    int _trader_id;
    int _item_id;
};

#endif
