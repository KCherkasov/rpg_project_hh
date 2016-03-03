#pragma once
#include "gtl_rpg.h"
#include "battle.h"

namespace gameplay
{
  using namespace gtl_rpg;

  const int LOCATION_LEVEL_SEED = 3; //���������� �������� ������� ��� ��������� �������
  const int GLOBAL_MAP_SIZE = 32;    //������ ���������� ����� (����� �������)

  struct TLocationIgData //��������� ������ ������� (������������� ��������������� �������)
  {
    int combat_probs[MAX_PACKS_COUNT][PAIR_ARR_SIZE]; //������ ������������ ������ ����� ����� ������������� ����. ������ ������� ����� ��������� �� MAX_PACKS_COUNT ������ ����� �����, ������ ����� - ������ ���� � ���� ������, ������ - ����������� ������ ����
    int trader_probs[TK_SIZE];                        //�����������  ������ ������ ����� ��������� � ������ �������
    int levels[PAIR_ARR_SIZE];                        //������� ������� - ������ � ������� �������, � �������� ������� ������������� ����������� ��������� � ������� ������������ �����
    bool has_been;                                    //������, ����������, ��� �� �������� � ���� �������  
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
  	  static gameplay::TLocationIgData generate(database::TLocationStData *tmp, player::Player *pl); //������� ��������� ������� �� ��������� ������� ��� ������� ��������� (��� ������� ���������) ������
  	  static bool on_enter(TLocationIgData *curr_loc);                                               //������� �������� ������� ��������� � ����������� ��� ����� � �������
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
