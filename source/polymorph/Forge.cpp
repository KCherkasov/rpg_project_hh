#include "Forge.h"

Forge::Forge() {
  _database = NULL;
}

Forge::Forge(char* db_name) {
  ConnectDatabase(db_name);
}

Forge::~Forge() {
  CloseDatabase();
}

int Forge::ConnectDatabase(void* db_name) {
  int response;
  response = sqlite3_open16(db_name, &_database);
  return response;
}

int Forge::CloseDatabase() {
  while (true) {
    if (sqlite3_close(_database) != SQLITE_BUSY) {
      break;
    }
  }
  return OK_CODE;
}

int Forge::get_slots(int query_id, int** slots)
{
  delete[] *slots;
  *slots = new int[ES_SIZE];
  int* buf = new int[ES_SIZE + 1];
  int response;
  sqlite3_stmt *statement;
  response = sqlite3_prepare16(_database, (wchar_t*)L"select id, head, chest, hands, boots, legs, trinket1, trinket2, trinket3, trinket4, weapon1, weapon2 from 'slots' where id=?", -1, &statement, 0);
  sqlite3_bind_int(statement, 1, query_id);
  sqlite3_step(statement);
  for (size_t i = 0; i < ES_SIZE + 1; ++i) {
    buf[i] = sqlite3_column_int(statement, i);
  }
  for (size_t i = 1; i < ES_SIZE + 1; ++i) {
    *slots[i-1] = buf[i];
  }
  delete[] buf;
  sqlite3_finalize(statement);
  return OK_CODE;
}

int Forge::get_stat_reqs(int query_id, int** reqs) {
  delete[] *reqs;
  *reqs = new int[CS_SIZE];
  int* buf = new int[CS_SIZE + 1];
  sqlite3_stmt *statement;
  int response;
  response = sqlite3_prepare16(_database, (wchar_t*)L"select id, stat1, stat2, stat3, stat4, stat5, stat6, stat7, stat8 from 'stat_reqs' where id=?", -1, &statement, 0);
  sqlite3_bind_int(statement, 1, query_id);
  sqlite3_step(statement);
  for (size_t i = 0; i < CS_SIZE + 1; ++i) {
    buf[i] = sqlite3_column_int(statement, i);
  }
  for (size_t i = 1; i < CS_SIZE + 1; ++i) {
    *reqs[i - 1] = buf[i];
  }
  delete[] buf;
  sqlite3_finalize(statement);
  return OK_CODE;
}

int Forge::get_stat_bons(int query_id, int** bons) {
  delete[] *bons;
  *bons = new int[CS_SIZE];
  int* buf = new int[CS_SIZE + 1];
  sqlite3_stmt *statement;
  int response;
  response = sqlite3_prepare16(_database, (wchar_t*)L"select id, stat1, stat2, stat3, stat4, stat5, stat6, stat7, stat8 from 'stat_bons' where id=?", -1, &statement, 0);
  sqlite3_bind_int(statement, 1, query_id);
  sqlite3_step(statement);
  for (size_t i = 0; i < CS_SIZE + 1; ++i) {
    buf[i] = sqlite3_column_int(statement, i);
  }
  for (size_t i = 1; i < CS_SIZE + 1; ++i) {
    *bons[i - 1] = buf[i];
  }
  delete[] buf;
  sqlite3_finalize(statement);
  return OK_CODE;
}

int Forge::get_manufacturer_data(int query_id, int kind, unsigned char** manufacturer_name, double* bonus) {
  sqlite3_stmt *statement;
  delete[] *manufacturer_name;
  *manufacturer_name = new unsigned char[NAMESTRING_SIZE];
  sqlite3_prepare16(_database,(wchar_t*)L"select id, manufacturer_name, pistol_bonus, smg_bonus, assault_bonus, sniper_bonus, melee_bonus, light_bonus, medium_bonus, heavy_bonus, trinket_bonus from 'manufacturers' where id=?", -1, &statement, 0);
  if (query_id != FREE_INDEX) {
    sqlite3_bind_int(statement,1,query_id);
  } else {
  	srand(static_cast<unsigned int>(time(0)));
    sqlite3_bind_int(statement,1, rand() % MANUFACTURERS_COUNT + 1); 
  }
  sqlite3_step(statement);
  *manufacturer_name = const_cast<unsigned char*>(sqlite3_column_text(statement,1));
  int bonus_value = sqlite3_column_int(statement, kind+2);
  if (bonus_value == 1) {
    *bonus = MANUFACTURER_BONUS;
  } else {
    *bonus = 1.0;
  }
  sqlite3_finalize(statement);
  return OK_CODE;
}

int Forge::get_item_name(int query_id, int item_kind, unsigned char** item_name) {
  sqlite3_stmt *statement;
  delete[] *item_name;
  *item_name = new unsigned char[NAMESTRING_SIZE];
  sqlite3_prepare16(_database, (wchar_t*)L"select id, item_name from 'item_names' where id=?", -1, &statement, 0);
  if (query_id != FREE_INDEX) {
    sqlite3_bind_int(statement, 1, item_kind * 10 + query_id);
  } else {
  	srand(static_cast<unsigned int>(time(0)));
    sqlite3_bind_int(statement, 1, item_kind * 10 + rand() % NAMES_COUNT + 1);
  }
  sqlite3_step(statement);
  *item_name = const_cast<unsigned char*>(sqlite3_column_text(statement, 1));
  sqlite3_finalize(statement);
  return OK_CODE;
}

int Forge::get_equipable_prototype(int query_id, TEquipablePrototype* prototype) {
  int return_code = OK_CODE;
  sqlite3_stmt* statement;
  int response = sqlite3_prepare16(_database, (wchar_t*)L"select id, name_id, manufacturer_id, cost, damdef, description, distance, item_kind, slots_template from 'EquipableItems' where id=?", -1, &statement, 0);
  sqlite3_bind_int(statement, 1, query_id);
  sqlite3_step(statement);

  prototype->kind = sqlite3_column_int(statement, 7);
  prototype->_cost = sqlite3_column_int(statement, 3);
  prototype->_damdef = sqlite3_column_int(statement, 4);
  prototype->_description = const_cast<unsigned char*>(sqlite3_column_text(statement, 5));
  prototype->_manufacturer_id = sqlite3_column_int(statement,2);
  prototype->_name_id = sqlite3_column_int(statement,1);
  int slots_preset = sqlite3_column_int(statement, 8);
  prototype->_distance = sqlite3_column_int(statement, 6);

  int* tmp_reqs = NULL;
  int query = get_stat_reqs(query_id, &tmp_reqs);
  for (size_t i = 0; i < CS_SIZE; ++i) {
    prototype->_stat_reqs[i] = tmp_reqs[i];
  }
  delete[] tmp_reqs;

  int* tmp_bons = NULL;
  query = get_stat_bons(query_id, &tmp_bons);
  for(size_t i = 0; i < CS_SIZE; ++i) {
    prototype->_stat_bons[i] = tmp_bons[i];
  }
  delete[] tmp_bons;
  
  int* tmp_slots = NULL;
  query = get_slots(slots_preset, &tmp_slots);
  for(size_t i = 0; i < ES_SIZE; ++i) {
    prototype->_slots[i] = tmp_slots[i];
  }
  delete[] tmp_slots;
  
  sqlite3_finalize(statement);
  return return_code;
}

int Forge::MakeEquipableItem(int query_id, int level, EquipableItem* spawned) {
  TEquipablePrototype prototype;
  int return_code = get_equipable_prototype(query_id, &prototype);
  unsigned char* item_name = NULL;
  unsigned char* manufacturer = NULL;
  double bonus = 0;
  return_code = get_item_name(prototype._name_id, prototype.kind, &item_name);
  return_code = get_manufacturer_data(prototype._manufacturer_id, prototype.kind, &manufacturer, &bonus);
  
  EquipableItem* item = NULL;
  if (prototype._slots[ES_WEAPON1] || prototype._slots[ES_WEAPON2]) {
    if (prototype._distance > 0) {
      item = new RangedWeapon(prototype, item_name, manufacturer, level);
	} else {
      item = new MeleeWeapon(prototype, item_name, manufacturer, level);
	}
  }
  if (prototype._slots[ES_HEAD]) {
    item = new Head(prototype, item_name, manufacturer, level);
  }
  if (prototype._slots[ES_CHEST]) {
    item = new Chest(prototype, item_name, manufacturer, level);
  }
  if (prototype._slots[ES_HANDS]) {
    item = new Hands(prototype, item_name, manufacturer, level);
  }
  if (prototype._slots[ES_BOOTS]) {
    item = new Boots(prototype, item_name, manufacturer, level);
  }
  if (prototype._slots[ES_LEGS]) {
    item = new Legs(prototype, item_name, manufacturer, level);
  }
  if (prototype._slots[ES_TRINKET1] || prototype._slots[ES_TRINKET2] || prototype._slots[ES_TRINKET3] || prototype._slots[ES_TRINKET4]) {
    item = new Trinket(prototype, item_name, manufacturer, level);
  }
  spawned = item;
  return return_code;
}

int Forge::MakeItem(int query_id, int level, Item* spawned) {
  EquipableItem* item = NULL;
  MakeEquipableItem(query_id, level, item);
  spawned = item;
  return OK_CODE;
}


