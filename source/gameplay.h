#pragma once
#include "gtl_rpg.h"
#include "battle.h"

namespace gameplay
{
  using namespace gtl_rpg;

  const int LOCATION_LEVEL_SEED = 3; //полуширина разброса уровней при генерации локации
  const int GLOBAL_MAP_SIZE = 32;    //размер глобальной карты (число локаций)

  struct TLocationIgData //структура данных локации (внутриигровой сгенерированный вариант)
  {
    int combat_probs[MAX_PACKS_COUNT][PAIR_ARR_SIZE]; //массив вероятностей спавна паков мобов определенного типа. Каждой локации можно приписать до MAX_PACKS_COUNT разных типов мобов, первое число - индекс пака в базе данных, второе - вероятность спавна пака
    int trader_probs[TK_SIZE];                        //вероятности  спавна разных типов торговцев в данной локации
    int levels[PAIR_ARR_SIZE];                        //разброс уровней - нижняя и верхняя границы, в пределах которых определеяется ассортимент торговцев и уровень появляющихся мобов
    bool has_been;                                    //флажок, отражающий, был ли персонаж в этой локации  
  };

  //
  void copy_location_data(struct TLocationIgData *from, struct TLocationIgData *to);
  //
  void swap_location_data(struct TLocationIgData *from, struct TLocationIgData *to);
  //
  void clear_location_data(struct TLocationIgData *data);
  
  class Location
  {
  	public:
  	  static gameplay::TLocationIgData generate(database::TLocationStData *tmp, player::Player *pl); //функция генерации локации по заданному шаблону под уровень входящего (для первого посещения) игрока
  	  static bool on_enter(TLocationIgData *curr_loc);                                               //функция проверки наличия торговцев и противников при входе в локацию
  }
  
  class GlobalMap
  {
    public:
    	
      //
      GlobalMap();
      //
      GlobalMap(TLocationIgData *inp_map, int map_sz, short plr_pos);
      //
      ~GlobalMap();
      //
      short get_player_position();
      //
      void set_player_position(short value);
      //
      gameplay::TLocationIgData get_location(int ind);
      //
      void set_location(TLocationIgData *inp_loc, int inp_sz, int start_ind);

    private:

      short player_position;                //
      TLocationIgData map[GLOBAL_MAP_SIZE]; //
  }
  
}
