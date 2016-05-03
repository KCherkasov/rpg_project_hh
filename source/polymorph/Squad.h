#ifndef SQUAD_H
#define SQUAD_H

#include <vector>

#include "AliveGameObject.h"
#include "Forge.h"
#include "Location.h"
#include "GruntMonster.h"
#include "DamagerMonster.h"
#include "SupportMonster.h"
#include "CommonMonster.h"
#include "QuestMonster.h"
#include "prototypes.h"

class Squad {
  public:
    Squad();
    Squad(int pack_id);
    virtual ~Squad() {}
    int get_pack_id() { return _pack_id; }
    void set_pack_id(int value) { _pack_id = value; }
    
	int get_member_index(AliveGameObject* &to_find, int &result);
    int get_member_address(AliveGameObject* &result, int to_find);
    
    std::vector<AliveGameObject*> _members;
    
  protected:
    int _pack_id;
};

#endif
