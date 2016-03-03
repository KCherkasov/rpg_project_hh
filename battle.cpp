#pragma once

#include "battle.h"

void battle::copy_mob_data(struct TMobIgData *from, struct TMobIgData *to)
{
	to->faction = from->faction;
	to->def = from->def;
	to->level = from->level;
	to->role = from->role; 
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		to->dmg[i] = from->dmg[i]; 
		to->hp[i] = from->hp[i];
	}
	to->loot = from->loot;
	to->ini = from->ini;
	to->is_leader = from->is_leader;
	to->is_mass_leader = from->is_mass_leader;
}

void battle::swap_mob_data(struct TMobIgData *from, struct TMobIgData *to)
{
	TMobIgData buf;
	copy_mob_data(to, &buf);
	copy_mob_data(from, to);
	copy_mob_data(&buf, from);
}

void battle::clear_mob_data(struct TMobIgData *data)
{
	data->faction = FREE_INDEX;
	
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
	    data->hp[i] = FREE_INDEX;
		data->dmg[i] = FREE_INDEX;
	}
	data->def = FREE_INDEX;
	data->role = NR_NONDEF;
	data->loot = FREE_INDEX;
	data->ini = FREE_INDEX;
}

void battle::copy_action_data(TAction *from, TAction *to)
{
  to->id = from->id;
  for (int i = 0; i < PAIR_ARR_SIZE; ++i)
  {
    to->sender_ids[i] = from->sender_ids[i];
    to->target_ids[i] = from->target_ids[i];
  }
}

void battle::swap_action_data(TAction *from, TAction *to)
{
  TAction buf;
  copy_action_data(to, &buf);
  copy_action_data(from, to);
  copy_action_data(&buf, from);
}

void battle::clear_action_data(TAction *data)
{
  data->id;
  for (int i = 0; i < PAIR_ARR_SIZE; ++i)
  {
    data->sender_ids[i] = FREE_INDEX;
	data->target_ids[i] = FREE_INDEX;
  }
}



battle::TMobIgData battle::Mob::spawn(TMobIgData *inp_data)
{
  TMobIgData mob_data;
  copy_mob_data(inp_data, &mob_data); //загрузка моба из сохраненных данных
  return mob_data;
}

battle::TMobIgData battle::Mob::spawn(database::TMobStData *inp_data)
{
  TMobIgData mob_data;
  clear_mob_data(&mob_data); //преинициализация данных моба
  mob_data.ini = inp_data->ini; 
  mob_data.def = inp_data->def; 
  mob_data.faction = inp_data->faction; 
  mob_data.loot = inp_data->loot; 
  mob_data.level = START_LEVEL; 
  mob_data.hp[1] = inp_data->hp;
  for (int i = 0; i < PAIR_ARR_SIZE; ++i)
  {
      mob_data.dmg[i] = inp_data->dmg[i];
  }
  //определение ролевой модели моба и применение соответствующих модификаторов
  //изначально все мобы принадлежат к стандартному типу NR_NONDEF, но с вероятностью 20%
  //могут изменить тип на танка, дамагера или лекаря
  {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = NR_GRUNT; i < NR_SIZE; ++i)
    {
      int rnd = rand() % PERCENT_MOD_CAP; 
      if (inp_data->roles[i])
      {
        switch (i)
        {
          case NR_GRUNT:
          {
            if (rnd <= BASE_TANK_PROB)
            {
              mob_data.role = NR_GRUNT;
            }
            break;
          }
          case NR_DMG:
          {
            if (rnd <= BASE_DAMAGER_PROB)
            {
              mob_data.role = NR_DMG;
            }
            break;
          }
          case NR_SUPPORT:
          {
            if (rnd <= BASE_SUPPORT_PROB)
            {
              mob_data.role = NR_SUPPORT;
            }
            break;
          }
        }
      }
      //если шаблон поведения больше не стандартный, прервать цикл
      if (mob_data.role != NR_NONDEF)
      {
        break;
      }
    }
  }
  //применение модификаторов
  switch (mob_data.role)
  {
    case NR_NONDEF:
    {
      double tmp_hp, tmp_dmg, tmp_def;  
      tmp_hp = mob_data.hp[1] * NONDEF_HP_MODIFIER;
      mob_data.hp[1] = round(tmp_hp);
      mob_data.hp[0] = mob_data.hp[1];
      tmp_def = mob_data.def*NONDEF_DEF_MODIFIER;
      mob_data.def = round(tmp_def);
      tmp_dmg = mob_data.dmg[0] * NONDEF_DMG_MODIFIER;
      mob_data.dmg[0] = round(tmp_dmg);
      tmp_dmg = mob_data.dmg[1] * NONDEF_DMG_MODIFIER;
      mob_data.dmg[1] = round(tmp_dmg);
      break;
    }
    case NR_GRUNT:
    {
      double tmp_hp, tmp_dmg, tmp_def;
      tmp_hp = mob_data.hp[1] * GRUNT_HP_MODIFIER;
      mob_data.hp[1] = round(tmp_hp);
      mob_data.hp[0] = mob_data.hp[1];
      tmp_def = mob_data.def * GRUNT_DEF_MODIFIER;
      mob_data.def = round(tmp_def);
      tmp_dmg = mob_data.dmg[0] * GRUNT_DMG_MODIFIER;
      mob_data.dmg[0] = round(tmp_dmg);
      tmp_dmg = mob_data.dmg[1] * GRUNT_DMG_MODIFIER;
      mob_data.dmg[1] = round(tmp_dmg);
      break;
    }
    case NR_DMG:
    {
      double tmp_hp, tmp_dmg, tmp_def;
      tmp_hp = mob_data.hp[1] * DAMAGER_HP_MODIFIER;
      mob_data.hp[1] = round(tmp_hp);
      mob_data.hp[0] = mob_data.hp[1];
      tmp_def = mob_data.def * DAMAGER_DEF_MODIFIER;
      mob_data.def = round(tmp_def);
      tmp_dmg = mob_data.dmg[0] * DAMAGER_DMG_MODIFIER;
      mob_data.dmg[0] = round(tmp_dmg);
      tmp_dmg = mob_data.dmg[1] * DAMAGER_DMG_MODIFIER;
      mob_data.dmg[1] = round(tmp_dmg);
      break;
    }
    case NR_SUPPORT:
    {
      double tmp_hp, tmp_dmg, tmp_def;
      tmp_hp = mob_data.hp[1] * SUPPORT_HP_MODIFIER;
      mob_data.hp[1] = round(tmp_hp);
      mob_data.hp[0] = mob_data.hp[1];
      tmp_def = mob_data.def * SUPPORT_DEF_MODIFIER;
      mob_data.def = round(tmp_def);
      tmp_dmg = mob_data.dmg[0] * SUPPORT_DMG_MODIFIER;
      mob_data.dmg[0] = round(tmp_dmg);
      tmp_dmg = mob_data.dmg[1] * SUPPORT_DMG_MODIFIER;
      mob_data.dmg[1] = round(tmp_dmg);
      break;
    }
  }
  return mob_data;
}

battle::TMobIgData battle::Mob::spawn(database::TMobStData *inp_data, int low_level_cap, int high_level_cap)
{
  TMobIgData mob_data;
  clear_mob_data(&mob_data); //преинициализация данных моба
  mob_data.ini = inp_data->ini;
  mob_data.def = inp_data->def;
  mob_data.faction = inp_data->faction;
  mob_data.loot = inp_data->loot;
  mob_data.level = START_LEVEL;
  mob_data.hp[1] = inp_data->hp;
  for (int i = 0; i < PAIR_ARR_SIZE; ++i)
  {
    mob_data.dmg[i] = inp_data->dmg[i];
  }
  srand(static_cast<unsigned int>(time(0)));
  //определение уровня генерируемого моба
  int rnd = rand() % (high_level_cap - low_level_cap) + low_level_cap;
  mob_data.level = rnd;
  //если уровень моба выше начального
  if (mob_data.level > START_LEVEL)
  {
    //начинаем модификацию ХП и наносимого урона
    for (int i = 0; i < (mob_data.level - START_LEVEL); ++i)
    {
      double tmp_hp, tmp_dmg, tmp_def;
      tmp_hp = mob_data.hp[1] * (1.0 + HP_CAP_RAISE);
      mob_data.hp[1] = round(tmp_hp);
      tmp_dmg = mob_data.dmg[0] * (1.0 + MOB_DMG_RAISE);
      mob_data.dmg[0] = round(tmp_dmg);
      tmp_dmg = mob_data.dmg[1] * (1.0 + MOB_DMG_RAISE);
      mob_data.dmg[1] = round(tmp_dmg);
      tmp_def = mob_data.def*(1.0 + MOB_DEF_RAISE);
      mob_data.def = round(tmp_def);
    }
    mob_data.hp[0] = mob_data.hp[1];
  }
  //определение ролевой модели моба и применение соответствующих модификаторов
  //изначально все мобы принадлежат к стандартному типу NR_NONDEF, но с вероятностью 20%
  //могут изменить тип на танка, дамагера или лекаря
  {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = NR_GRUNT; i < NR_SIZE; ++i)
    {
      int rnd = rand() % PERCENT_MOD_CAP;
      if (inp_data->roles[i] == true)
      {
        switch (i)
        {
          case NR_GRUNT:
          {
            if (rnd <= BASE_TANK_PROB)
            {
              mob_data.role = NR_GRUNT;
            }
            break;
          }
          case NR_DMG:
          {
            if (rnd <= BASE_DAMAGER_PROB)
            {
              mob_data.role = NR_DMG;
            }
            break;
          }
          case NR_SUPPORT:
          {
            if (rnd <= BASE_SUPPORT_PROB)
            {
              mob_data.role = NR_SUPPORT;
            }
            break;
          }
        }
      }
      //если шаблон поведения больше не стандартный, прервать цикл
      if (mob_data.role != NR_NONDEF)
      {
        break;
      }
    }
  }
  //применение модификаторов
  switch (mob_data.role)
  {
    case NR_NONDEF:
    {
      double tmp_hp, tmp_dmg, tmp_def;
      tmp_hp = mob_data.hp[1] * NONDEF_HP_MODIFIER;
      mob_data.hp[1] = round(tmp_hp);
      mob_data.hp[0] = mob_data.hp[1];
      tmp_def = mob_data.def*NONDEF_DEF_MODIFIER;
      mob_data.def = round(tmp_def);
      tmp_dmg = mob_data.dmg[0] * NONDEF_DMG_MODIFIER;
      mob_data.dmg[0] = round(tmp_dmg);
      tmp_dmg = mob_data.dmg[1] * NONDEF_DMG_MODIFIER;
      mob_data.dmg[1] = round(tmp_dmg);
      break;
    }
    case NR_GRUNT:
    {
      double tmp_hp, tmp_dmg, tmp_def;
      tmp_hp = mob_data.hp[1] * GRUNT_HP_MODIFIER;
      mob_data.hp[1] = round(tmp_hp);
      mob_data.hp[0] = mob_data.hp[1];
      tmp_def = mob_data.def * GRUNT_DEF_MODIFIER;
      mob_data.def = round(tmp_def);
      tmp_dmg = mob_data.dmg[0] * GRUNT_DMG_MODIFIER;
      mob_data.dmg[0] = round(tmp_dmg);
      tmp_dmg = mob_data.dmg[1] * GRUNT_DMG_MODIFIER;
      mob_data.dmg[1] = round(tmp_dmg);
      break;
    }
    case NR_DMG:
    {
      double tmp_hp, tmp_dmg, tmp_def;
      tmp_hp = mob_data.hp[1] * DAMAGER_HP_MODIFIER;
      mob_data.hp[1] = round(tmp_hp);
      mob_data.hp[0] = mob_data.hp[1];
      tmp_def = mob_data.def * DAMAGER_DEF_MODIFIER;
      mob_data.def = round(tmp_def);
      tmp_dmg = mob_data.dmg[0] * DAMAGER_DMG_MODIFIER;
      mob_data.dmg[0] = round(tmp_dmg);
      tmp_dmg = mob_data.dmg[1] * DAMAGER_DMG_MODIFIER;
      mob_data.dmg[1] = round(tmp_dmg);
      break;
    }
    case NR_SUPPORT:
    {
      double tmp_hp, tmp_dmg, tmp_def;
      tmp_hp = mob_data.hp[1] * SUPPORT_HP_MODIFIER;
      mob_data.hp[1] = round(tmp_hp);
      mob_data.hp[0] = mob_data.hp[1];
      tmp_def = mob_data.def * SUPPORT_DEF_MODIFIER;
      mob_data.def = round(tmp_def);
      tmp_dmg = mob_data.dmg[0] * SUPPORT_DMG_MODIFIER;
      mob_data.dmg[0] = round(tmp_dmg);
      tmp_dmg = mob_data.dmg[1] * SUPPORT_DMG_MODIFIER;
      mob_data.dmg[1] = round(tmp_dmg);
      break;
    }
  }
  return mob_data;
}

void battle::Mob::Check_Leadership(TMobIgData *mob_data, bool already_have_a_leader, bool already_have_a_mass_leader)
{
  srand(static_cast<unsigned int>(time(0)));
  int rnd = rand();
  rnd %= PERCENT_MOD_CAP;
  if ((!already_have_a_leader) && (rnd <= BASE_LEADER_PROB))
  {
    mob_data->is_leader = true;
    already_have_a_leader = true;
    double tmp_hp, tmp_dmg, tmp_def;
    tmp_hp = mob_data->hp[1] * LEADER_HP_MODIFIER;
    mob_data->hp[1] = round(tmp_hp);
    mob_data->hp[0] = mob_data->hp[1];
    tmp_def = mob_data->def * LEADER_DEF_MODIFIER;
    mob_data->def = round(tmp_def);
    tmp_dmg = mob_data->dmg[0] * LEADER_DMG_MODIFIER;
    mob_data->dmg[0] = round(tmp_dmg);
    tmp_dmg = mob_data->dmg[1] * LEADER_DMG_MODIFIER;
    mob_data->dmg[1] = round(tmp_dmg);
    //проверка на то, является ли лидер масс-лидером
    if (!already_have_a_mass_leader)
    {
      int rnd = rand();
      rnd %= PERCENT_MOD_CAP;
      if (rnd <= BASE_MASS_LEADER_PROB)
      {
        mob_data->is_mass_leader = true;
        already_have_a_mass_leader = true;
        double tmp_hp, tmp_dmg, tmp_def;
        tmp_hp = mob_data->hp[1] * MASS_LEADER_HP_MODIFIER;
        mob_data->hp[1] = round(tmp_hp);
        mob_data->hp[0] = mob_data->hp[1];
        tmp_def = mob_data->def * MASS_LEADER_DEF_MODIFIER;
        mob_data->def = round(tmp_def);
        tmp_dmg = mob_data->dmg[0] * MASS_LEADER_DMG_MODIFIER;
        mob_data->dmg[0] = round(tmp_dmg);
        tmp_dmg = mob_data->dmg[1] * MASS_LEADER_DMG_MODIFIER;
        mob_data->dmg[1] = round(tmp_dmg);
      }
    }
  }
}

battle::TItemIgData battle::Item::spawn(database::TItemStData *data)
{
	TItemIgData item_data;
	clear_item(&item_data);
	srand(static_cast<unsigned int>(time(0)));
	item_data.cost = data->cost;
	item_data.def = data->def;
	item_data.description = data->description;
	item_data.disposable = data->disposable;
	item_data.dist = data->dist;
	item_data.hpbons = data->hpbons;
	item_data.ifstack = data->ifstack;
	item_data.kind = data->kind;
	item_data.lvlreq = data->lvlreq;
	item_data.manufacturer = data->manufacturer;
	item_data.name = data->name;
	item_data.ntbons = data->ntbons;
	item_data.usable = data->usable;
	item_data.stack = 1;
	item_data.durability[1] = data->durability;
	item_data.durability[0] = item_data.durability[1];
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		item_data.dmg[i] = data->dmg[i];
	}
	for (int i = 0; i < STATS_COUNT; ++i)
	{
		item_data.statbons[i] = data->statbons[i];
		item_data.statreq[i] = data->statreq[i];
	}
	for (int i = 0; i < ES_SIZE; ++i)
	{
		item_data.slots[i] = data->slots[i];
	}
	//
	item_data.rarity = IR_TRASH;
	for (int i = 0; i < IR_SIZE; ++i)
	{
		int rnd = rand() % PERCENT_MOD_CAP;
		if (rnd < data->drop_rates[i])
		{
			item_data.rarity = TItemRareness(i);
		}
	}
	//
	{
		double qmod = 0.0;
		for (int i = 0; i < IR_SIZE; ++i)
		{
			if ((i >= item_data.rarity) && (item_data.rarity > IR_TRASH))
			{
				qmod += QUALITY_MODIFIER;
			}
			else
			{
				qmod -= QUALITY_MODIFIER;
			}
		}
		double tmp = item_data.cost;
		tmp *= (1.0 + qmod);
		item_data.cost = round(tmp);
		tmp = item_data.def;
		tmp *= (1.0 + qmod);
		item_data.def = round(tmp);
		for (int i = 0; i < STATS_COUNT; ++i)
		{
			tmp = item_data.statbons[i];
			tmp *= (1.0 + qmod);
			item_data.statbons[i] = round(tmp);
		}
		for (int i = 0; i < PAIR_ARR_SIZE; ++i)
		{
			tmp = item_data.dmg[i];
			tmp *= (1.0 + qmod);
			item_data.dmg[i] = round(tmp);
		}
	}
	return item_data;
}

gtl_rpg::TItemIgData battle::Item::spawn(database::TItemStData *data, int llc, int hlc)
{
	TItemIgData item_data;
	clear_item(&item_data);
	srand(static_cast<unsigned int>(time(0)));
	item_data.cost = data->cost;
	item_data.def = data->def;
	item_data.description = data->description;
	item_data.disposable = data->disposable;
	item_data.dist = data->dist;
	item_data.hpbons = data->hpbons;
	item_data.ifstack = data->ifstack;
	item_data.kind = data->kind;
	item_data.lvlreq = rand() % (hlc - llc) + llc; //уровень предмета определяется как случайное число от llс до hlc
	item_data.manufacturer = data->manufacturer;
	item_data.name = data->name;
	item_data.ntbons = data->ntbons;
	item_data.usable = data->usable;
	item_data.stack = 1;
	item_data.durability[1] = data->durability;
	item_data.durability[0] = item_data.durability[1];
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		item_data.dmg[i] = data->dmg[i];
	}
	for (int i = 0; i < STATS_COUNT; ++i)
	{
		item_data.statbons[i] = data->statbons[i];
		item_data.statreq[i] = data->statreq[i];
	}
	for (int i = 0; i < ES_SIZE; ++i)
	{
		item_data.slots[i] = data->slots[i];
	}
	//
	item_data.rarity = IR_TRASH;
	for (int i = 0; i < IR_SIZE; ++i)
	{
		int rnd = rand() % PERCENT_MOD_CAP;
		if (rnd < data->drop_rates[i])
		{
			item_data.rarity = TItemRareness(i);
		}
	}
	//
	if (item_data.lvlreq > START_LEVEL)
	{
		double tmp;
		for (int i = 0; i < (item_data.lvlreq - 1); ++i)
		{
			tmp = item_data.cost;
			tmp *= (1.0 + COST_MODIFIER);
			item_data.cost = round(tmp);
			tmp = item_data.def;
			tmp *= (1.0 + DAMDEF_MODIFIER);
			item_data.def = round(tmp);
			for (int j = 0; j < PAIR_ARR_SIZE; ++j)
			{
				tmp = item_data.dmg[j];
				tmp *= (1.0 + DAMDEF_MODIFIER);
				item_data.dmg[j] = round(tmp);
			}
			for (int j = 0; j < STATS_COUNT; ++j)
			{
				tmp = item_data.statbons[j];
				tmp *= (1.0 + STAT_MODIFER);
				item_data.statbons[j] = round(tmp);
			}
		}
	}
	//
	{
		double qmod = 0.0;
		for (int i = 0; i < IR_SIZE; ++i)
		{
			if ((i >= item_data.rarity) && (item_data.rarity > IR_TRASH))
			{
				qmod += QUALITY_MODIFIER;
			}
			else
			{
				qmod -= QUALITY_MODIFIER;
			}
		}
		double tmp = item_data.cost;
		tmp *= (1.0 + qmod);
		item_data.cost = round(tmp);
		tmp = item_data.def;
		tmp *= (1.0 + qmod);
		item_data.def = round(tmp);
		for (int i = 0; i < STATS_COUNT; ++i)
		{
			tmp = item_data.statbons[i];
			tmp *= (1.0 + qmod);
			item_data.statbons[i] = round(tmp);
		}
		for (int i = 0; i < PAIR_ARR_SIZE; ++i)
		{
			tmp = item_data.dmg[i];
			tmp *= (1.0 + qmod);
			item_data.dmg[i] = round(tmp);
		}
	}
	return item_data;
}

battle::Battlefield::Battlefield()
{
}

battle::Battlefield::~Battlefield()
{
}

int battle::Battlefield::spawn_prob(int spawned, int dp)
{
  int res = PERCENT_CAP - spawned*dp;
  if (res < ZERO)
  {
    res = ZERO;
  }
  return res;
}

bool battle::Battlefield::pack_has_leader(int pack_id)
{
  bool res = false;
  for (int i = 0; i < enemies[pack_id].size(); ++i)
  {
    if (enemies[pack_id][i].is_leader)
    {
      res = true;
      break;
    }
  }
  return res;
}

bool battle::Battlefield::have_mass_leader()
{
  bool res = false;
  for (int i = 0; i < enemies.size(); ++i)
  {
    for (int j = 0; j < enemies[i].size(); ++j)
    {
      if (enemies[i][j].is_mass_leader)
      {
        res = true;
        break;
      }
    }
    if (res)
    {
      break;
    }
  }
  return res;
}

void battle::Battlefield::spawn_new_mob(database::Database *db, int mob_id, int pack_id, int llc, int hlc)
{
  enemies[pack_id].resize(enemies[pack_id].size() + 1);
  database::TMobStData mob_tmp = db->get_mob(mob_id);
  TMobIgData spawned = Mob::spawn(&mob_tmp, llc, hlc);
  copy_mob_data(&spawned, &(enemies[pack_id][enemies[pack_id].size() - 1]));
  Mob::Check_Leadership(&(enemies[pack_id][enemies[pack_id].size() - 1]), pack_has_leader(pack_id), have_mass_leader());
}

void battle::Battlefield::spawn_new_pack(database::Database *db, int mob_id, int llc, int hlc)
{
  srand(static_cast<unsigned int>(time(0)));
  enemies.resize(enemies.size() + 1);
  enemies[enemies.size() - 1].clear();
  for (int i = 0; i < PACK_MAX_SIZE; ++i)
  {
    int rnd = rand() % PERCENT_MOD_CAP;
    if (rnd <= spawn_prob(enemies[enemies.size() - 1].size(), db->get_mob(mob_id).dp))
    {
      spawn_new_mob(db, mob_id, enemies.size() - 1, llc, hlc);
    }
    else
    {
      break;
    }
  }
}

void battle::Battlefield::clear_dead(database::Database *db, int llc, int hlc)
{
  srand(static_cast<unsigned int>(time(0)));
  //сканируем всех отспавненных мобов
  for (int i = 0; i < enemies.size(); ++i)
  {
    //пустые паки пропускаем, если есть хоть один моб, сканируем пак
    if (enemies[i].size() > ZERO)
    {
      for (int j = 0; j < enemies[i].size(); ++j)
      {
        //если текущее ХП моба равно 0, генерируем с него лут, добавляем награды в деньгах и опыте в общий пул и удаляем его из пака
        if (enemies[i][j].hp[0] == ZERO)
        {
          database::TLootList list;
          clear_loot_list(&list);
          list = db->get_loot_list(enemies[i][j].loot);
          double tmp_cash = list.cash;
          double tmp_exp = list.exp;
          //если уровень моба выше первого, наращиваем награду в деньгах и опыте пропорционально уровню и помещаем ее в общий пул
          if (enemies[i][j].level > START_LEVEL)
          {
            for (int k = START_LEVEL; k < enemies[i][j].level; ++k)
            {
              tmp_cash *= (1.0 + CASH_RAISE);
              tmp_exp *= (1.0 + EXP_RAISE);
            }
          }
          //если моб был лидером, применяем лидерские модификаторы опыта и денег к награде и дебафаем пак
          if (enemies[i][j].is_leader)
          {
            tmp_cash *= LEADER_CASH_MODIFIER;
            tmp_exp *= LEADER_EXP_MODIFIER;
            //дебафаем пак лидера за его смерть
            for (int k = 0; k < enemies[i].size(); ++k)
            {
              if (k != j)
              {
                double tmp;
                for (int l = 0; l < PAIR_ARR_SIZE; ++l)
                {
                  tmp = enemies[i][k].dmg[l];
                  tmp /= (LEADER_DMG_MODIFIER * PACK_DEBUFF_MODIFIER);
                  enemies[i][k].dmg[l] = round(tmp);
                }
                tmp = enemies[i][k].def;
                tmp /= (LEADER_DEF_MODIFIER * PACK_DEBUFF_MODIFIER);
                enemies[i][k].def = round(tmp);
                tmp = enemies[i][k].hp[1];
                tmp /= (LEADER_HP_MODIFIER * PACK_DEBUFF_MODIFIER);
                enemies[i][k].hp[1] = round(tmp);
                if (enemies[i][k].hp[0] > enemies[i][k].hp[1])
                {
                  enemies[i][k].hp[0] = enemies[i][k].hp[1];
                }
                else
                {
                  tmp = enemies[i][k].hp[0];
                  tmp /= (LEADER_HP_MODIFIER * PACK_DEBUFF_MODIFIER);
                  enemies[i][k].hp[0] = round(tmp);
                }
              }
            }
            //если моб был масс-лидером, применяем масс-лидерские модификаторы опыта и денег
            if (enemies[i][j].is_mass_leader)
            {
              double tmp;
              tmp_cash *= MASS_LEADER_CASH_MODIFIER;
              tmp_exp *= MASS_LEADER_EXP_MODIFIER;
              //запускаем дебаф всех живых мобов
              for (int k = 0; k < enemies.size(); ++k)
              {
                for (int l = 0; l < enemies[k].size(); ++l)
                {
                  //модификатор 0.1 применяется, дабы избежать бафа параметров мобов - !!! ПРИ ИЗМЕНЕНИИ МАСС-ЛИДЕРСКИХ МОДИФИКАТОРОВ НЕОБХОДИМО ПЕРЕСМОТРЕТЬ НЕОБХОДИМОСТЬ ПРИМЕНЕНИЯ 0.1 !!!
                  tmp = enemies[k][l].def;
                  tmp /= (MASS_LEADER_DEF_MODIFIER * (0.1 + PACK_DEBUFF_MODIFIER));
                  enemies[k][l].def = round(tmp);
                  tmp = enemies[k][l].hp[1];
                  tmp /= (MASS_LEADER_HP_MODIFIER * (0.1 + PACK_DEBUFF_MODIFIER));
                  enemies[k][l].hp[1] = round(tmp);
                  if (enemies[k][l].hp[0]>enemies[k][l].hp[1])
                  {
                    enemies[k][l].hp[0] = enemies[k][l].hp[1];
                  }
                  else
                  {
                    tmp = enemies[k][l].hp[0];
                    tmp /= (MASS_LEADER_HP_MODIFIER * (0.1 + PACK_DEBUFF_MODIFIER));
                    enemies[k][l].hp[0] = round(tmp);
                  }
                  for (int m = 0; m < PAIR_ARR_SIZE; ++m)
                  {
                    tmp = enemies[k][l].dmg[m];
                    tmp /= (MASS_LEADER_DMG_MODIFIER * (0.1 + PACK_DEBUFF_MODIFIER));
                    enemies[k][l].dmg[m] = round(tmp);
                  }
                }
              }
            }
          }
          //вносим награды в деньгах и опыте в общий пул боя
          reward_cash += round(tmp_cash);
          reward_exp += round(tmp_exp);
          //сканируем лут-лист по предметам и пытаемся генерить каждый предмет по списку в максимально возможном количестве
          for (int k = 0; k < LOOT_LIST_SIZE; ++k)
          {
            for (int l = 0; l < list.loot[k].max_quant; ++l)
            {
              int rnd = rand() % PERCENT_MOD_CAP;
              if (rnd <= list.loot[k].poss)
              {
                database::TItemStData data = db->get_item(list.loot[k].id);
                loot.resize(loot.size() + 1);
                TItemIgData item = Item::spawn(&data,llc,hlc);
                copy_item(&item, &(loot[loot.size() - 1]));
              }
            }
          }
          enemies[i].erase(enemies[i].begin() + j);
        }
      }
    }
  }
}

battle::TAction battle::AI::select(TNPCRole role, player::Player *pl, Battlefield *bf, int i, int j)
{
  //выбираем нужный паттерн ИИ
  switch (role)
  {
    case NR_NONDEF:
    {
      return AI::nondef_ai(pl, bf, i, j);
    }
    case NR_GRUNT:
    {
      return AI::grunt_ai(pl, bf, i, j);
    }
    case NR_DMG:
    {
      return AI::damager_ai(pl, bf, i, j);
    }
    case NR_SUPPORT:
    {
      return AI::healer_ai(pl, bf, i, j);
    }
  }
}

battle::TAction battle::AI::healer_ai(player::Player *pl, Battlefield *bf, int i, int j)
{
  //
  TAction res;
  res.id = AL_IDLE;
  res.sender_ids[0] = i;
  res.sender_ids[1] = j;
  unsigned int variants[AL_SIZE] = { ZERO }; //массив значений полезности вариантов действий
  for (int k = 0; k < bf->enemies.size(); ++k)
  {
    for (int l = 0; l < bf->enemies[k].size(); ++l)
    {
      if ((k != i) && (l != j))
      {
        
      }
    }
  }
  return res;
}

battle::TAction battle::AI::damager_ai(player::Player *pl, Battlefield *bf, int i, int j)
{
  //
  TAction res;
  res.id = AL_IDLE;
  res.sender_ids[0] = i;
  res.sender_ids[1] = j;
  unsigned int variants[AL_SIZE] = { ZERO }; //массив значений полезности вариантов действий
  for (int k = 0; k < bf->enemies.size(); ++k)
  {
    for (int l = 0; l < bf->enemies[k].size(); ++l)
    {
      if ((k != i) && (l != j))
      {
        
      }
    }
  }
  return res;
}

battle::TAction battle::AI::grunt_ai(player::Player *pl, Battlefield *bf, int i, int j)
{
  //
  TAction res;
  res.id = AL_IDLE;
  res.sender_ids[0] = i;
  res.sender_ids[1] = j;
  unsigned int variants[AL_SIZE] = { ZERO }; //массив значений полезности вариантов действий
  //
  for (int k = 0; k < bf->enemies.size(); ++k)
  {
    for (int l = 0; l < bf->enemies[k].size(); ++l)
    {
      if ((k != i) && (l != j))
      {
        
      }
    }
  }
  return res;
}

battle::TAction battle::AI::nondef_ai(player::Player *pl, Battlefield *bf, int i, int j)
{
  //
  TAction res;
  res.id = AL_IDLE;
  res.sender_ids[0] = i;
  res.sender_ids[1] = j;
  unsigned int variants[AL_SIZE] = { ZERO }; //массив значений полезности вариантов действий
  for (int k = 0; k < bf->enemies.size(); ++k)
  {
    for (int l = 0; l < bf->enemies[k].size(); ++l)
    {
      if ((k != i) && (l != j))
      {
        
      }
    }
  }
  return res;
}
