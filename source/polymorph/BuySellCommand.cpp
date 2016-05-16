#include "BuySellCommand.h"

BuySellCommand::BuySellCommand(World* &world, bool is_buying, int trader_id, int item_id) : BackendCommand() {
  _world = world;
  _is_buying = is_buying;
  _trader_id = trader_id;
  _item_id = item_id;
}

int BuySellCommand::execute() {
  if (_world != NULL) {
    if (_trader_id > FREE_INDEX && _trader_id < MERCHANTS_COUNT) {
      if (_world->_current_location->_traders[_trader_id] != NULL) {
        if (_is_buying) {
          if (_item_id > FREE_INDEX && _item_id < VENDOR_CAPACITY) {
            _world->_player->buy(_world->_current_location->_traders[_trader_id], _item_id);
		  }
	    } else {
          if (_item_id > FREE_INDEX && _item_id < BACKPACK_SIZE) {
            _world->_player->sell(_world->_current_location->_traders[_trader_id], _item_id);
		  }
	    }
	  }
	}
  }
  return 0;
}
