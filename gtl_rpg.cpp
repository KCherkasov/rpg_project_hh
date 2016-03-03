#include "gtl_rpg.h"

bool gtl_rpg::is_pair_variable(int arsz, int elsz)
{
	bool res = false;
	if (arsz / elsz == PAIR_ARR_SIZE)
	{
		res = true;
	}
	return res;
}

void gtl_rpg::copy_item(struct TItemIgData *from, struct TItemIgData *to)
{
	to->name = from->name;
	to->cost = from->cost;
	to->def = from->def;
	to->ifstack = from->ifstack;
	to->usable = from->usable;
	to->kind = from->kind;
	to->disposable = from->disposable;
	to->dist = from->dist;
	to->lvlreq = from->lvlreq;
	to->manufacturer = from->manufacturer;
	for (int i = 0; i < STATS_COUNT; ++i)
	{
		to->statreq[i] = from->statreq[i];
		to->statbons[i] = from->statbons[i];
	}
	to->stack = from->stack;
	to->ifstack = from->ifstack;
	to->ntbons = from->ntbons;
	to->hpbons = from->hpbons;
	to->description = from->description;
	to->rarity = from->rarity;
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		to->durability[i] = from->durability[i];
		to->dmg[i] = from->dmg[i];
	}
	for (int i = ES_HEAD; i < ES_SIZE; ++i)
	{
		to->slots[i] = from->slots[i];
	}
}

void gtl_rpg::swap_item(struct TItemIgData *from, struct TItemIgData *to)
{
	TItemIgData buf;
	copy_item(to, &buf);
	copy_item(from, to);
	copy_item(&buf, from);
}

void gtl_rpg::clear_item(struct TItemIgData *item)
{
	//������� ������� � ���������� � ���������������
	for (int i = 0; i < STATS_COUNT; ++i)
	{
		item->statbons[i] = FREE_INDEX;
		item->statreq[i] = FREE_INDEX;
	}
	item->lvlreq = FREE_INDEX; //������ ���������� � ������
	item->hpbons = FREE_INDEX; //������� ������������� ��
	item->ntbons = FREE_INDEX; //������� ������������ �������
	item->dist = FREE_INDEX;   //������� ��������������
	item->kind = FREE_INDEX;   //������� ������� ���� ��������
	item->name = FREE_INDEX;   //������� ��������
	item->description = FREE_INDEX; //������� ��������
	item->manufacturer = FREE_INDEX; //������� ������� �������������
	item->stack = FREE_INDEX; //������� ������������� �����
	item->ifstack = false; //������� ����������� ��������
	item->cost = FREE_INDEX; //������� ����
	item->rarity = IR_TRASH; //������� ��������
	item->def = FREE_INDEX; //������� ������
	item->dmg[0] = FREE_INDEX; //������� ���-> �����
	item->dmg[1] = FREE_INDEX; //������� ����-> �����
	item->durability[0] = FREE_INDEX; //������� ������� ���������
	item->durability[1] = FREE_INDEX; //������� ����-> ���������
	//��������� ��������� �������� � ���� ���� ���������
	for (int i = 0;i < ES_SIZE; ++i)
	{
		item->slots[i] = true;
	}
	item->disposable = false; //������� ���� ����������
	item->usable = false; //������ ������� ��������������
}

void gtl_rpg::copy_buff_data(struct TBuffData *from, struct TBuffData to)
{
	to->from = from->from;
	to->to = from->to;
	to->is_const = from->is_const;
	to->kind = from->kind;
	to->time = from->time;
	to->eff_kind = from->eff_kind;
	for (int i = 0 i < PAIR_ARR_SIZE; ++i)
	{
		to->effect[i] = from->effect[i];
	}
}

void gtl_rpg::swap_buff_data(struct TBuffData *from, struct TBuffData *to)
{	
	TBuffData buf;
	copy_buff_data(to, &buf);
	copy_buff_data(from, to);
	copy_buff_data(&buf, from);
}

void gtl_rpg::clear_buff_data(struct TBuffData *data)
{
	data->from = FREE_INDEX;
	data->to = FREE_INDEX;
	data->eff_kind = PA_NONDEF;
	data->is_const = false;
	data->kind = FREE_INDEX;
	data->time = FREE_INDEX;
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		data->effect[i] = FREE_INDEX;
	}
}

void gtl_rpg::copy_maptile_data(struct TMapTile *from, struct TMapTile *to)
{
	to->id = from->id;
	to->obj[0] = from->obj[0];
	to->obj[1] = from->obj[1];
	to->passable = from->passable;
}

void gtl_rpg::swap_maptile_data(struct TMapTile *from, struct TMapTile *to)
{
	TMapTile buf;
	copy_maptile_data(to, &buf);
	copy_maptile_data(from, to);
	copy_maptile_data(&buf, from);
}

void gtl_rpg::clear_maptile_data(struct TMapTile *data)
{
	data->id = TL_NONDEF;
	data->obj[0] = FREE_INDEX;
	data->obj[1] = FREE_INDEX;
	data->passable = false;
}

}
