#ifndef ATTACK_H
#define ATTACK_H

#include "Action.h"
#include "Battlefield.h"
#include "AliveGameObject.h"
#include "PartyMember.h"
#include "GruntMonster.h"
#include "DamagerMonster.h"
#include "SupportMonster.h"
#include "CommonMonster.h"
#include "QuestMonster.h"
#include "Monster.h"

#include <ctime>
#include <cmath>
#include <cstdlib>
 
class Attack: public Action {
  public:
    Attack(Battlefield* battlefied, int sender_x_coord, int sender_y_coord, int target_x_coord, int target_y_coord);
    virtual ~Attack();
    int implement();
    AliveGameObject* get_sender();
    AliveGameObject* get_target();
    void set_sender(int* value);
    void set_target(int* value);
  protected:
  	int count_distance(int x1_coord, int y1_coord, int x2_coord, int y2_coord);
  	AliveGameObject* _sender;
  	AliveGameObject* _target;
  	int _distance;
};

#endif
