#ifndef EQUIPPED_H
#define EQUIPPED_H

#include "Inventory.h"
#include "prototypes.h"

class Equipped: public Inventory {
  public:
    Equipped(): _size(ES_SIZE) { new Item*[ES_SIZE] {NULL}; }
	virtual ~Equipped();
    int first_free_slot(int &result);
    int count_free_slots(int &result);	
    int add_item(Item* &new_item);
    int add_item(Item* &new_item, int index);
    int get_item(int index, Item* &result);
    int get_index(Item* &address);
    int remove_item(int to_delete);
    int swap_items(int from_slot, Inventory* &to_bag, int to_slot);
    int swap_items(int from_index, int to_index);
    int use_item(int index, AliveGameObject* &user);
    int get_size(int &result)
    void render() {}
  protected:
    int _size;
    Item** _content;
};

#endif
