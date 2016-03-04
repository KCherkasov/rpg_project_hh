#pragma once

#include <ctime>
#include <cmath>
#include <cstdlib>

#include "gtl_rpg.h"
#include "player.h"
#include "database.h"

namespace battle
{
  using namespace gtl_rpg;

  //NPC behavior template stat modifiers

  const int BASE_NONDEF_PROB = 40;               //base chance to spawn a common mob
  const int BASE_TANK_PROB = 20;                 //base chance to spawn a "tank" mob
  const int BASE_SUPPORT_PROB = 20;              //base chance to spawn a healer/supporter mob
  const int BASE_DAMAGER_PROB = 20;              //base chance to spawn a damager mob

  const int BASE_LEADER_PROB = 10;               //chance to spawn a pack leader leader
  const int BASE_MASS_LEADER_PROB = 20;          //chance to spawn a mass-leader

  const double NONDEF_HP_MODIFIER = 1.0;
  const double NONDEF_DMG_MODIFIER = 1.0;
  const double NONDEF_DEF_MODIFIER = 1.0;

  const double GRUNT_HP_MODIFIER = 1.50;
  const double GRUNT_DMG_MODIFIER = 0.50;
  const double GRUNT_DEF_MODIFIER = 2.25;

  const double SUPPORT_HP_MODIFIER = 0.75;
  const double SUPPORT_DMG_MODIFIER = 1.25;
  const double SUPPORT_DEF_MODIFIER = 0.50;

  const double DAMAGER_HP_MODIFIER = 0.50;
  const double DAMAGER_DMG_MODIFIER = 2.25;
  const double DAMAGER_DEF_MODIFIER = 0.75;

  const double LEADER_HP_MODIFIER = 1.50;
  const double LEADER_DMG_MODIFIER = 1.50;
  const double LEADER_DEF_MODIFIER = 1.50;
  const double LEADER_EXP_MODIFIER = 1.50;
  const double LEADER_CASH_MODIFIER = 1.50;

  const double MASS_LEADER_HP_MODIFIER = 1.25;
  const double MASS_LEADER_DMG_MODIFIER = 1.25;
  const double MASS_LEADER_DEF_MODIFIER = 1.25;
  const double MASS_LEADER_EXP_MODIFIER = 1.25;
  const double MASS_LEADER_CASH_MODIFIER = 1.25;

  const double PACK_DEBUFF_MODIFIER = 0.75;      //pack all-stat debuff when leader dies

  //=======================================================================================\\
  //=======================================================================================\\

  //=======================================================================================\\
  //<-----------------------------!AI action value modifiers!----------------------------->\\
  /*=======================================================================================*/
	
  const double NONDEF_IDLE_MOD = 1.0;
  const double NONDEF_MOVE_MOD = 1.0;
  const double NONDEF_CAST_MOD = 1.0;
  const double NONDEF_ATTACK_MOD = 1.0;
  const double NONDEF_COVER_MOD = 1.0;

  const double GRUNT_IDLE_MOD = 1.0;
  const double GRUNT_MOVE_MOD = 1.0;
  const double GRUNT_CAST_MOD = 1.0;
  const double GRUNT_ATTACK_MOD = 1.0;
  const double GRUNT_COVER_MOD = 1.0;

  const double DMG_IDLE_MOD = 1.0;
  const double DMG_MOVE_MOD = 1.0;
  const double DMG_CAST_MOD = 1.0;
  const double DMG_ATTACK_MOD = 1.0;
  const double DMG_COVER_MOD = 1.0;

  const double SUPPORT_IDLE_MOD = 1.0;
  const double SUPPORT_MOVE_MOD = 1.0;
  const double SUPPORT_CAST_MOD = 1.0;
  const double SUPPORT_ATTACK_MOD = 1.0;
  const double SUPPORT_COVER_MOD = 1.0;

  //=======================================================================================\\
  //=======================================================================================\\

  const int MAP_WIDTH = 128;
	
  enum TActionList { AL_IDLE, AL_MOVE, AL_CAST, AL_ATTACK, AL_COVER, AL_SIZE }; //availible actions per turn
	
  struct TMobIgData //mob data (in-game generated for battle)
  {
    int faction;
    int dmg[PAIR_ARR_SIZE];
    int hp[PAIR_ARR_SIZE];
    int def;
    int level;
	int loot;
	int ini;
	TNPCRole role;
    bool is_leader;
    bool is_mass_leader;
  };

  struct TAction //action data (for turn queue)
  {
    int sender_ids[PAIR_ARR_SIZE];
    int target_ids[PAIR_ARR_SIZE];
	TActionList  id;
  };

  void copy_mob_data(struct TMobIgData *from, struct TMobIgData *to);
  void swap_mob_data(struct TMobIgData *from, struct TMobIgData *to);
  void clear_mob_data(struct TMobIgData *data);
  void copy_action_data(struct TAction *from, struct TAction *to);
  void swap_action_data(struct TAction *from, struct TAction *to);
  void clear_action_data(struct TAction *data);

  class Mob  //in-game mobs spawner class
  {
    public:

      static battle::TMobIgData spawn(TMobIgData *inp_data);
      static battle::TMobIgData spawn(database::TMobStData *inp_data);
      static battle::TMobIgData spawn(database::TMobStData *inp_data, int low_level_cap, int high_level_cap);
      static void Check_Leadership(TMobIgData *mob_data, bool already_have_a_leader, bool already_have_a_mass_leader);

  };

  class Item //in-game items spawner class
  {
    public:

      static gtl_rpg::TItemIgData spawn(struct database::TItemStData *data);
      static gtl_rpg::TItemIgData spawn(struct database::TItemStData *data, int llc, int hlc);

  };

  class Battlefield //battle class (
  {
    public:

      Battlefield();
      ~Battlefield();
      int spawn_prob(int spawned, int dp);
      int total_enemies();
      void turn_sort(player::Player *pl);
      bool pack_has_leader(int pack_id);
      bool have_mass_leader();
      void spawn_new_mob(database::Database *db, int mob_id, int pack_id, int llc, int hlc);
      void spawn_new_pack(database::Database *db, int mob_id, int llc, int hlc);
      void clear_dead(database::Database *db, int llc, int hlc);

      std::vector<std::vector<TMobIgData> > enemies; //spawned mob packs  vector

      private:

        int reward_cash;
        int reward_exp;
        std::vector<TItemIgData> loot;                //gained loot vector
        std::vector<TBuffData> buffs;                 //active buffs/dots/hots
        std::vector<int[PAIR_ARR_SIZE]> turn_order;

	};

    class AI //AI handler class
    {
      public:

        //main action selector
        static battle::TAction select(TNPCRole role, player::Player *pl, Battlefield *bf, int i, int j);

      private:

        //action selectors for different NPC behaviors
        static battle::TAction healer_ai(player::Player *pl, Battlefield *bf, int i, int j);
        static battle::TAction damager_ai(player::Player *pl, Battlefield *bf, int i, int j);
        static battle::TAction grunt_ai(player::Player *pl, Battlefield *bf, int i, int j);
        static battle::TAction nondef_ai(player::Player *pl, Battlefield *bf, int i, int j);

    };
}
