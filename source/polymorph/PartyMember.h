#ifndef PARTYMEMBER_H
#define PARTYMEMBER_H

#include "AliveGameObject.h"
#include "Forge.h"
#include "prototypes.h"

class PartyMember: public AliveGameObject {
  public:
    PartyMember(TPartyMemberPrototype &prototype, unsigned char* name, int level);
    virtual ~PartyMember();
    int get_stat(int index, int &result);
    int change_stat(int index, int value);
    int* get_stats();
    int get_salary() { return _salary; }
    int change_exp(int value);
    int get_money_earned() { return _money_earned; }
    int change_money_earned(int value);
    int get_killed_count() { return _killed_count; }
    int change_killed_count();
    int get_skill_points() { return _skill_points; }
    int get_unpaid_count() { return _unpaid_count; }
    int increase_unpaid_count() { return ++_unpaid_count; }
    int reset_unpaid_count() { _unpaid_count = 0; return 0; }
    int level_up();
    int what(std::string &out);
    int get_pic_name(std::string &out);

    Inventory* _equipped;
  	
  protected:
    int* _stats;
    int _killed_count;
    int _money_earned;
    int _salary;
    int _skill_points;
    int _unpaid_count;
    bool _gender;
};

#endif
