#pragma once
#include "gtl_rpg.h"

namespace player
{
  using namespace gtl_rpg;

  const int FIRST_LEVELUP_CAP = 100;    //кап опыта для набора второго уровня
  const int INITIAL_STATS_VALUE = 10;   //значение параметров персонажа первого уровня
  const int LEVELUP_SP_GRANT = 5;       //число очков навыков, получаемых при повышении уровня
  const int HP_PER_STAT_POINT = 10;     //число ХП, прибавляемых к максимуму за каждое очко выносливости персонажа

  enum TInventorySections { IS_NONDEF = FREE_INDEX, IS_EQUIPPED, IS_BACKPACK, IS_BANK, IS_STORAGE, IS_SIZE }; //тип разделов инвентаря персонажа
  //IS_EQUIPPED-надетое снаряжение, IS_BACKPACK-сумка, IS_BANK-банк, IS_STORAGE-хранилище

  struct TInventoryData //структура данных о предметах игрока
  {
	  TItemIgData equipped[ES_SIZE];       //надетое снаряжение
	  TItemIgData backpack[BACKPACK_SIZE]; //содержимое сумки
	  TItemIgData bank[BANK_SIZE];         //содержимое банковского хранилища
	  TItemIgData storage[STORAGE_SIZE];   //содержимое хранилища на базе
	  int cash;                            //деньги
  };

  struct TPlayerData //структура данных персонажа игрока
  {
    std::string name;       //имя
    int level;              //уровень
    int nutrition;          //сытость
    int exp[PAIR_ARR_SIZE]; //опыт (текущий/до нового уровня)
    int hp[PAIR_ARR_SIZE];  //уровень ХП (текущий/максимальный)
    int sp;                 //доступные очки навыков
    int stats[STATS_COUNT]; //характеристики персонажа
    //Индексы характеристик в массиве:
    //0-меткость 1-реакция 2-сила 3-выносливость
    //4-внимательность 5-интеллект 6-убеждение 7-скорость
  };

  //функция копирования экипировки
  void copy_inventory_equipped(struct TInventoryData *from, struct TInventoryData *to);
  //функция копирования сумки
  void copy_inventory_backpack(struct TInventoryData *from, struct TInventoryData *to);
  //функция копирования банка
  void copy_inventory_bank(struct TInventoryData *from, struct TInventoryData *to);
  //функция копирования хранилища
  void copy_inventory_storage(struct TInventoryData *from, TInventoryData *to);
  //функция полного копирования инвентаря
  void copy_inventory_all(struct TInventoryData *from, struct TInventoryData *to);
  //функция обмена списками экипировки
  void swap_inventory_equipped(struct TInventoryData *from, struct TInventoryData *to);
  //функция обмена сумками
  void swap_inventory_backpack(struct TInventoryData *from, struct TInventoryData *to);
  //функция обмена банками
  void swap_inventory_bank(struct TInventoryData *from, struct TInventoryData *to);
  //функция обмена хранилищами
  void swap_inventory_storage(struct TInventoryData *from, struct TInventoryData *to);
  //функция полного обмена инвентарями
  void swap_inventory_all(struct TInventoryData *from, struct TInventoryData *to);
  //функция очистки экипировки
  void clear_inventory_equipped(struct TInventoryData *inv);
  //функция очистки сумки
  void clear_inventory_backpack(struct TInventoryData *inv);
  //функция очистки банка
  void clear_inventory_bank(struct TInventoryData *inv);
  //функция очистки хранилища
  void clear_inventory_storage(struct TInventoryData *inv);
  //функция полной очистки инвентаря
  void clear_inventory_all(struct TInventoryData *inv);
  //функция проверки, свободен ли слот инвентаря
  bool inventory_slot_is_free(struct gtl_rpg::TItemIgData *slot);
  //функция поиска первого пустого слота в сумке
  int inventory_first_free_backpack(struct TInventoryData *data);
  //функция поиска первого пустого слота в банке
  int inventory_first_free_bank(struct TInventoryData *data);
  //функция поиска первого пустого слота в хранилище
  int inventory_first_free_storage(struct TInventoryData *data);
  //функция подсчета количества свободных слотов в сумке
  int inventory_count_free_slots_backpack(struct TInventoryData *data);
  //функция подсчета количества свободных слотов в банке
  int inventory_count_free_slots_bank(struct TInventoryData *data);
  //функция подсчета количества свободных слотов в хранилище
  int inventory_count_free_slots_storage(struct TInventoryData *data);
  //функция копирования информации о персонаже игрока
  void copy_player_data(struct TPlayerData *from, struct TPlayerData *to);
  //функция обмена информацией о персонаже игрока
  void swap_player_data(struct TPlayerData *from, struct TPlayerData *to);
  //функция очистки информации о персонаже игрока
  void clear_player_data(struct TPlayerData *data);

  //класс персонажа игрока
  class Player
  {
    public:
	//конструкторы/деструкторы

    //базовый конструктор
    Player();
    //конструктор для загрузки сохраненной игры
    Player(struct TPlayerData inp_char, struct TInventoryData inp_items);
    //деструктор класса
    ~Player();

    //методы	

    //обработка ситуаций и действий пользователя с характеристиками и уровнями

    //функция повышения характеристики персонажа
    void stat_up(int stat_index);
    //функция повышения уровня персонажа
    void level_up();

    //обработка манипуляций пользователя с инвентарем

    //функция добавления предмета в сумку персонажа (возвращаемое значение - истина, если предмет есть куда положить, ложь - если сумка переполнена)
    bool add_item(struct TItemIgData *item);
    //функция удаления предмета из инвентаря
    void remove_item(TInventorySections section, int slot);
    //функция обмена местами двух слотов в инвентаре
    bool swap_items(TInventorySections from_section, int from_slot, TInventorySections to_section, int to_slot);

    //get-/set-функции

    //
    int get_stat(int ind);
    //
    int get_level();
    //
    int get_sp();
    //
    int get_exp(int ind);
    //
    int get_hp(int ind);
    //
    int get_nutrition();
    //
    std::string get_name();
    //
    gtl_rpg::TItemIgData get_item(TInventorySections section, int ind);
    //
    void set_stat(int ind, int value, TFieldEditorKind kind);
    //
    void set_level(int value, TFieldEditorKind kind);
    //
    void set_sp(int value, TFieldEditorKind kind);
    //
    void set_nutrition(int value, TFieldEditorKind kind);
	//
    void set_name(std::string value);
    //
    void set_exp(int ind, int value, TFieldEditorKind kind);
    //
    void set_hp(int ind, int value, TFieldEditorKind kind);
	
    //

    //функция извлечения информации о персонаже
    player::TPlayerData eject_pdata();
    //функция извлечения информации об инвентаре
    player::TInventoryData eject_idata();

    private:
      TPlayerData char_data; //параметры персонажа
      TInventoryData items;  //предметы на персонаже и во всех доступных хранилищах
  };

}