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

  //константы вероятностей выбора различных моделей поведения при генерации моба

  const int BASE_NONDEF_PROB = 40;               //константа базовой вероятности генерации стандартного моба
  const int BASE_TANK_PROB = 20;                 //константа базовой вероятности генерации моба-танка
  const int BASE_SUPPORT_PROB = 20;              //константа базовой вероятности генерации моба-лекаря
  const int BASE_DAMAGER_PROB = 20;              //константа базовой вероятности генерации моба-дамагера

  const int BASE_LEADER_PROB = 10;               //вероятность генерации лидера
  const int BASE_MASS_LEADER_PROB = 20;          //вероятность генерации масс-лидера

  const double NONDEF_HP_MODIFIER = 1.0;         //модификатор ХП стандартного моба
  const double NONDEF_DMG_MODIFIER = 1.0;        //модификатор урона стандартного моба
  const double NONDEF_DEF_MODIFIER = 1.0;        //модификатор защиты стандартного моба

  const double GRUNT_HP_MODIFIER = 1.50;         //модификатор ХП танка
  const double GRUNT_DMG_MODIFIER = 0.50;        //модификатор урона танка
  const double GRUNT_DEF_MODIFIER = 2.25;        //модификатор защиты танка

  const double SUPPORT_HP_MODIFIER = 0.75;       //модификатор ХП целителя
  const double SUPPORT_DMG_MODIFIER = 1.25;      //модификатор урона целителя
  const double SUPPORT_DEF_MODIFIER = 0.50;      //модификатор защиты целителя

  const double DAMAGER_HP_MODIFIER = 0.50;       //модификатор ХП дамагера
  const double DAMAGER_DMG_MODIFIER = 2.25;      //модификатор урона дамагера
  const double DAMAGER_DEF_MODIFIER = 0.75;      //модификатор защиты дамагера

  const double LEADER_HP_MODIFIER = 1.50;        //модификатор ХП лидера
  const double LEADER_DMG_MODIFIER = 1.50;       //модификатор урона лидера
  const double LEADER_DEF_MODIFIER = 1.50;       //модификатор защиты лидера
  const double LEADER_EXP_MODIFIER = 1.50;       //модификатор опыта за убийство лидера
  const double LEADER_CASH_MODIFIER = 1.50;      //модификатор денежной награды за убийство лидера

  const double MASS_LEADER_HP_MODIFIER = 1.25;   //модификатор ХП масс-лидера
  const double MASS_LEADER_DMG_MODIFIER = 1.25;  //модификатор урона масс-лидера
  const double MASS_LEADER_DEF_MODIFIER = 1.25;  //модификатор защиты масс-лидера
  const double MASS_LEADER_EXP_MODIFIER = 1.25;  //модификатор опыта за убийство масс-лидера (применяется совместно с лидерским модификатором)
  const double MASS_LEADER_CASH_MODIFIER = 1.25; //модификатор денежной награды за убийство масс-лидера (применяется совместно с лидерским модификатором)

  const double PACK_DEBUFF_MODIFIER = 0.75;      //модификатор для расчета коэффициента дебафов при смерти лидера

  //=======================================================================================\\
  //=======================================================================================\\

  //=======================================================================================\\
  //<------------------------!модификаторы ценности действий для ИИ!---------------------->\\
  //<-данный раздел содержит константы, отражающие веса различных вариантов действий для-->\\
  //<-----------------------------разных паттернов ИИ  мобов.----------------------------->\\
  //=======================================================================================\\
	
  const double NONDEF_IDLE_MOD = 1.0; //модификатор вероятности ничего не делать для стандартного моба
  const double NONDEF_MOVE_MOD = 1.0; //модификатор вероятности перемещения для стандартного моба
  const double NONDEF_CAST_MOD = 1.0; //модификатор вероятности применения особой способности для стандартного моба
  const double NONDEF_ATTACK_MOD = 1.0; //модификатор вероятности атаковать противника для стандатного моба
  const double NONDEF_COVER_MOD = 1.0; //модификатор вероятности использовать укрытие для стандартного моба

  const double GRUNT_IDLE_MOD = 1.0; //модификатор вероятности ничего не делать для моба-танка
  const double GRUNT_MOVE_MOD = 1.0; //модификатор вероятности перемещения для моба-танка
  const double GRUNT_CAST_MOD = 1.0; //модификатор вероятности использовать особую способность для моба-танка
  const double GRUNT_ATTACK_MOD = 1.0; //модификатор вероятности атаковать противника для моба-танка
  const double GRUNT_COVER_MOD = 1.0; //модификатор вероятности занять укрытие для моба-танка

  const double DMG_IDLE_MOD = 1.0; //модификатор вероятности ничего не делать для моба-дд
  const double DMG_MOVE_MOD = 1.0; //модификатор вероятности перемещения для моба-дд
  const double DMG_CAST_MOD = 1.0; //модификатор вероятности использовать особую способности для моба-дд
  const double DMG_ATTACK_MOD = 1.0; //модификатор вероятности атаковать противника для моба-дд
  const double DMG_COVER_MOD = 1.0;	//модификатор вероятности занять укрытие для моба-дд

  const double SUPPORT_IDLE_MOD = 1.0; //модификатор вероятности ничего не делать для моба-саппорта
  const double SUPPORT_MOVE_MOD = 1.0; //модификатор вероятности перемещения для моба-саппорта
  const double SUPPORT_CAST_MOD = 1.0; //модификатор вероятности использования особой способности для моба-саппорта
  const double SUPPORT_ATTACK_MOD = 1.0; //модификатор вероятности атаковать противника для моба-саппорта
  const double SUPPORT_COVER_MOD = 1.0;  //модификатор вероятности занять укрытие для моба-саппорта

  //=======================================================================================\\
  //=======================================================================================\\

  const int MAP_WIDTH = 128;		    //размер карты в тайлах (карта считается квадратной)
	
  enum TActionList { AL_IDLE, AL_MOVE, AL_CAST, AL_ATTACK, AL_COVER, AL_SIZE }; //тип доступных действий
  //AL_IDLE-пропуск хода, AL_MOVE-переместиться, AL_ATTACK-атаковать, AL_CAST-применить способность, AL_COVER-занять укрытие
	
  struct TMobIgData //структура данных сгенерированного моба (реально участвует в бою)
  {
    int faction;            //фракция
    int dmg[PAIR_ARR_SIZE]; //наносимый мобом урон
    int hp[PAIR_ARR_SIZE];  //ХП моба
    int def;                //защита моба
    int level;              //уровень моба
	int loot;               //индекс лут-листа моба в базе данных (типового)
	int ini;                //инициатива моба
	TNPCRole role;          //шаблон поведения моба
    bool is_leader;         //является ли лидером
    bool is_mass_leader;    //является ли масс-лидером
  };

  struct TAction //структура данных дейсвия (для помещения в очередь хода)
  {
    int sender_ids[PAIR_ARR_SIZE]; //идентификаторы совершающего действие (id пака и id внутри пака, для игрока ставить PLAYER_ID)
    int target_ids[PAIR_ARR_SIZE]; //идентификаторы цели (id пака и id внутри пака, для игрока ставить PLAYER_ID, для перемещения - координаты тайла на карте)
	TActionList  id;               //тип действия 
  };

  //функция копирования сгенерированного моба
  void copy_mob_data(struct TMobIgData *from, struct TMobIgData *to);
  //функция обмена местами сгенерированных мобов в паке
  void swap_mob_data(struct TMobIgData *from, struct TMobIgData *to);
  //функция очистки сгенерированного моба
  void clear_mob_data(struct TMobIgData *data);
  //функция копирования данных действия
  void copy_action_data(struct TAction *from, struct TAction *to);
  //функция обмена местами двух действий
  void swap_action_data(struct TAction *from, struct TAction *to);
  //функция очистки данных действия
  void clear_action_data(struct TAction *data);

  //класс-плодильщик мобов
  class Mob
  {
    public:

      //функция генерации моба (использовать для загрузки сохраненной игры, если есть бой)
      static battle::TMobIgData spawn(TMobIgData *inp_data);
      //функция генерации моба (использовать для генерации моба первого уровня)
      static battle::TMobIgData spawn(database::TMobStData *inp_data);
      //функция генерации моба (использовать для генерации моба заданного уровня)
      static battle::TMobIgData spawn(database::TMobStData *inp_data, int low_level_cap, int high_level_cap);
      //функция проверки, является ли данный моб лидером либо масс-лидером
      static void Check_Leadership(TMobIgData *mob_data, bool already_have_a_leader, bool already_have_a_mass_leader);

	};

	class Item //класс-плодильщик предметов
	{
      public:

        //функция создания предмета первого уровня по заданному шаблону
        static gtl_rpg::TItemIgData spawn(struct database::TItemStData *data);
        //функция создания предмета определенного уровня по заданному шаблону
        static gtl_rpg::TItemIgData spawn(struct database::TItemStData *data, int llc, int hlc);

	};

	class Battlefield //класс поля боя
	{
	  public:

        //конструкторы/деструкторы

        //базовый конструктор класса
        Battlefield();
        //базовый деструктор класса
        ~Battlefield();

        //методы

        //функция расчета вероятности добавления нового моба в пак
        int spawn_prob(int spawned, int dp);
        //функция подсчета числа противников
        int total_enemies();
        //функция определения очередности хода
        void turn_sort(player::Player *pl);
        //
        bool pack_has_leader(int pack_id);
        //
        bool have_mass_leader();
        //спавн нового моба
        void spawn_new_mob(database::Database *db, int mob_id, int pack_id, int llc, int hlc);
        //спавн нового пака
        void spawn_new_pack(database::Database *db, int mob_id, int llc, int hlc);
        //функция очистки от трупов
        void clear_dead(database::Database *db, int llc, int hlc);

        std::vector<std::vector<TMobIgData> > enemies; //вектор паков противников

      private:

        int reward_cash;                              //суммарная денежная награда за бой
        int reward_exp;                               //суммарная награда в опыте за бой
        std::vector<TItemIgData> loot;                //вектор выпавшего лута
        std::vector<TBuffData> buffs;                 //вектор бафов/дотов/хотов
        std::vector<int[PAIR_ARR_SIZE]> turn_order;   //вектор очередности хода

	};

    //класс искусственного интеллекта
    class AI
    {
      public:

        //функция выбора действия
        static battle::TAction select(TNPCRole role, player::Player *pl, Battlefield *bf, int i, int j);

      private:

        //паттерн ИИ лекаря
        static battle::TAction healer_ai(player::Player *pl, Battlefield *bf, int i, int j);
        //паттерн ИИ дамагера
        static battle::TAction damager_ai(player::Player *pl, Battlefield *bf, int i, int j);
        //паттерн ИИ танка
        static battle::TAction grunt_ai(player::Player *pl, Battlefield *bf, int i, int j);
        //паттерн ИИ стандартного моба
        static battle::TAction nondef_ai(player::Player *pl, Battlefield *bf, int i, int j);

    };
}
