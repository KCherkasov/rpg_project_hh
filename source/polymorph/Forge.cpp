#include "Forge.h"

Forge::Forge() {
  _database = NULL;
}

Forge::Forge(const char* db_name) {
  std::string path;
  char buf[FILENAME_MAX];
  _getcwd(buf,sizeof(buf));
  path.append(buf);
  path.append("\\");
  path.append(db_name);
  ConnectDatabase(db_name);
  printf("%s\n\n",path.data());
}

Forge::~Forge() {
  CloseDatabase();
}

int Forge::ConnectDatabase(const char* db_name) {
  int response;
  response = sqlite3_open(db_name, &_database);
  if (response != SQLITE_OK) {
    printf("Error: %s\n", sqlite3_errmsg(_database));
  }
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

int Forge::get_slots(int query_id, int* &slots)
{
  delete[] slots;
  slots = new int[ES_SIZE];
  int* buf = new int[ES_SIZE + 1];
  int response;
  sqlite3_stmt *statement;
  response = sqlite3_prepare(_database, "select id, head, chest, hands, boots, legs, trinket1, trinket2, trinket3, trinket4, weapon1, weapon2 from 'slots' where id=?", -1, &statement, 0);
  sqlite3_bind_int(statement, 1, query_id);
  sqlite3_step(statement);
  for (size_t i = 0; i < ES_SIZE + 1; ++i) {
    buf[i] = sqlite3_column_int(statement, i);
  }
  for (size_t i = 1; i < ES_SIZE + 1; ++i) {
    slots[i-1] = buf[i];
  }
  delete[] buf;
  if (response != SQLITE_OK) {
    printf("Error: %s\n", sqlite3_errmsg(_database));
  }
  sqlite3_finalize(statement);
  return response;
}

int Forge::get_stat_reqs(int query_id, int* &reqs) {
  delete[] reqs;
  reqs = new int[CS_SIZE];
  int* buf = new int[CS_SIZE + 1];
  sqlite3_stmt *statement;
  int response;
  response = sqlite3_prepare(_database, "select id, stat0, stat1, stat2, stat3, stat4, stat5, stat6, stat7  from 'stat_reqs' where id=?", -1, &statement, 0);
  sqlite3_bind_int(statement, 1, query_id);
  sqlite3_step(statement);
  for (size_t i = 0; i < CS_SIZE + 1; ++i) {
    buf[i] = sqlite3_column_int(statement, i);
  }
  for (size_t i = 0; i < CS_SIZE; ++i) {
    reqs[i] = buf[i + 1];
  }
  delete[] buf;
  if (response != SQLITE_OK) {
    printf("Error: %s\n", sqlite3_errmsg(_database));
  }
  sqlite3_finalize(statement);
  return response;
}

int Forge::get_stat_bons(int query_id, int* &bons) {
  delete[] bons;
  bons = new int[CS_SIZE];
  int* buf = new int[CS_SIZE + 1];
  sqlite3_stmt *statement;
  int response;
  response = sqlite3_prepare(_database, "select id, stat0, stat1, stat2, stat3, stat4, stat5, stat6, stat7 from 'stat_bons' where id=?", -1, &statement, 0);
  sqlite3_bind_int(statement, 1, query_id);
  sqlite3_step(statement);
  for (size_t i = 0; i < CS_SIZE + 1; ++i) {
    buf[i] = sqlite3_column_int(statement, i);
  }
  for (size_t i = 0; i < CS_SIZE; ++i) {
    bons[i] = buf[i + 1];
  }
  delete[] buf;
  if (response != SQLITE_OK) {
    printf("Error: %s\n", sqlite3_errmsg(_database));
  }
  sqlite3_finalize(statement);
  return response;
}

int Forge::get_manufacturer_data(int query_id, int kind, unsigned char* &manufacturer_name, double* bonus) {
  sqlite3_stmt *statement;
  delete[] manufacturer_name;
  manufacturer_name = new unsigned char[NAMESTRING_SIZE] {};
  int response;
  response = sqlite3_prepare(_database,"select id, name, pistol_bonus, smg_bonus, assault_bonus, sniper_bonus, melee_bonus, light_bonus, medium_bonus, heavy_bonus, trinket_bonus from 'manufacturers' where id=?", -1, &statement, 0);
  if (query_id != FREE_INDEX) {
    sqlite3_bind_int(statement,1,query_id);
  } else {
  	srand(static_cast<unsigned int>(time(0)));
    sqlite3_bind_int(statement,1, rand() % MANUFACTURERS_COUNT + 1); 
  }
  sqlite3_step(statement);
  const unsigned char* tmp_name;
  tmp_name = sqlite3_column_text(statement,1);
  for (size_t i = 0; i < NAMESTRING_SIZE && tmp_name[i] != '\0'; ++i) {
    manufacturer_name[i] = tmp_name[i];
  }
  int bonus_value = sqlite3_column_int(statement, kind+2);
  if (bonus_value == 1) {
    *bonus = MANUFACTURER_BONUS;
  } else {
    *bonus = 1.0;
  }
  if (response != SQLITE_OK) {
    printf("Error: %s\n", sqlite3_errmsg(_database));
  }
  sqlite3_finalize(statement);
  delete[] tmp_name;
  return response;
}

int Forge::get_item_name(int query_id, int item_kind, unsigned char* &item_name) {
  sqlite3_stmt *statement;
  delete[] item_name;
  item_name = new unsigned char[NAMESTRING_SIZE] {};
  int response;
  response = sqlite3_prepare(_database, "select id, item_name from 'item_names' where id=?", -1, &statement, 0);
  if (query_id != FREE_INDEX) {
    sqlite3_bind_int(statement, 1, item_kind * 10 + query_id);
  } else {
  	srand(static_cast<unsigned int>(time(0)));
    sqlite3_bind_int(statement, 1, item_kind * 10 + rand() % NAMES_COUNT + 1);
  }
  sqlite3_step(statement);
  const unsigned char* tmp_name;
  tmp_name = sqlite3_column_text(statement, 1);
  for (size_t i = 0; i < NAMESTRING_SIZE && tmp_name[i] != '\0'; ++i) {
    item_name[i] = tmp_name[i];
  }
  if (response != SQLITE_OK) {
    printf("Error: %s\n", sqlite3_errmsg(_database));
  }
  sqlite3_finalize(statement);
  delete[] tmp_name;
  return response;
}

int Forge::get_equipable_prototype(int query_id, TEquipablePrototype* prototype) {
  int return_code = OK_CODE;
  sqlite3_stmt* statement;
  int response = sqlite3_prepare(_database, "select id, name_id, manufacturer_id, cost, damdef, description, distance, item_kind, slots_template from 'EquipableItems' where id=?", -1, &statement, 0);
  sqlite3_bind_int(statement, 1, query_id);
  sqlite3_step(statement);
  if (response != SQLITE_OK) {
    printf("Error: %s\n", sqlite3_errmsg(_database));
  }
  prototype->kind = sqlite3_column_int(statement, 7);
  prototype->_cost = sqlite3_column_int(statement, 3);
  prototype->_damdef = sqlite3_column_int(statement, 4);
  unsigned char* tmp_description = new unsigned char[DESCRSTRING_SIZE] {};
  delete[] prototype->_description;
  prototype->_description = new unsigned char[DESCRSTRING_SIZE] {};
  tmp_description = const_cast<unsigned char*>(static_cast<const unsigned char*>(sqlite3_column_blob(statement, 5)));
  for (size_t i = 0; i < DESCRSTRING_SIZE && tmp_description[i] != '\0'; ++i) {
    prototype->_description[i] = tmp_description[i];
  }
  delete[] tmp_description;
  prototype->_manufacturer_id = sqlite3_column_int(statement,2);
  prototype->_name_id = sqlite3_column_int(statement,1);
  int slots_preset = sqlite3_column_int(statement, 8);
  prototype->_distance = sqlite3_column_int(statement, 6);

  int* tmp_reqs = NULL;
  int query = get_stat_reqs(query_id, tmp_reqs);
  for (size_t i = 0; i < CS_SIZE; ++i) {
    prototype->_stat_reqs[i] = tmp_reqs[i];
  }
  delete[] tmp_reqs;

  int* tmp_bons = NULL;
  query = get_stat_bons(query_id, tmp_bons);
  for(size_t i = 0; i < CS_SIZE; ++i) {
    prototype->_stat_bons[i] = tmp_bons[i];
  }
  delete[] tmp_bons;
  
  int* tmp_slots = NULL;
  query = get_slots(slots_preset, tmp_slots);
  for(size_t i = 0; i < ES_SIZE; ++i) {
    prototype->_slots[i] = tmp_slots[i];
  }
  delete[] tmp_slots;
  sqlite3_finalize(statement);
  
  delete[] prototype->_name;
  delete[] prototype->_manufacturer;
  prototype->_name = new unsigned char[NAMESTRING_SIZE] {};
  prototype->_manufacturer = new unsigned char[NAMESTRING_SIZE] {};
  unsigned char* item_name = NULL;
  unsigned char* manufacturer = NULL;
  double bonus = 0;  
  return_code = get_item_name(prototype->_name_id, prototype->kind, item_name);
  for (size_t i = 0; i < NAMESTRING_SIZE && item_name[i] !='\0'; ++i) {
    prototype->_name[i] = item_name[i];
  }
  delete[] item_name;
  return_code = get_manufacturer_data(prototype->_manufacturer_id, prototype->kind, manufacturer, &bonus);
  for (size_t i = 0; i < NAMESTRING_SIZE && manufacturer[i] != '\0'; ++i) {
    prototype->_manufacturer[i] = manufacturer[i];
  }
  delete[] manufacturer;
  for (size_t i = 0; i < STATS_COUNT; ++i) {
    prototype->_stat_bons[i] *= bonus;
  }
  prototype->_damdef *= bonus;
  prototype->_cost *= bonus;
  return_code = response;
  return return_code;
}

int Forge::get_tile_prototype(int query_id, TTilePrototype* prototype) {
  int return_code = OK_CODE;
  sqlite3_stmt* statement;
  int response = sqlite3_prepare(_database, "select id, defense, passable, texture_id, name, description from 'Tiles' where id = ?", -1, &statement, 0);
  sqlite3_bind_int(statement, 1, query_id);
  sqlite3_step(statement);
  if(response != SQLITE_OK) {
    printf("Error: %s\n", sqlite3_errmsg(_database));
  }
  const unsigned char* tmp_name = new unsigned char[NAMESTRING_SIZE] {};
  const unsigned char* tmp_description = new unsigned char[DESCRSTRING_SIZE] {};
  prototype->_defense = sqlite3_column_int(statement, 1);
  prototype->_is_passable = (sqlite3_column_int(statement, 2) == 1);
  prototype->_texture = sqlite3_column_int(statement, 3);
  tmp_name = sqlite3_column_text(statement, 4);
  tmp_description = sqlite3_column_text(statement, 5);
  prototype->_name = new unsigned char[NAMESTRING_SIZE] {};
  for (size_t i = 0; i < NAMESTRING_SIZE && tmp_name[i] != '\0'; ++i) {
    prototype->_name[i] = tmp_name[i];
  }
  prototype->_description = new unsigned char[DESCRSTRING_SIZE] {};
  for (size_t i = 0; i < DESCRSTRING_SIZE && tmp_description[i] != '\0'; ++i) {
    prototype->_description[i] = tmp_description[i];
  }
  delete[] tmp_name;
  delete[] tmp_description;
  sqlite3_finalize(statement);
  
  return return_code;
}

int Forge::get_npc_prototype(int query_id, TNPCPrototype* prototype) {
  int return_code;
  sqlite3_stmt* statement;
  int response = sqlite3_prepare(_database, "select id, content_id, charge, name, description, speech from 'NPCs' where id=?", -1, &statement, 0);
  sqlite3_bind_int(statement, 1, query_id);
  sqlite3_step(statement);
  const unsigned char* tmp_name = new unsigned char[NAMESTRING_SIZE] {};
  const unsigned char* tmp_description = new unsigned char[DESCRSTRING_SIZE] {};
  const unsigned char* tmp_speech = new unsigned char[DESCRSTRING_SIZE] {};
  prototype->_name = new unsigned char[NAMESTRING_SIZE] {};
  prototype->_description = new unsigned char[DESCRSTRING_SIZE] {};
  prototype->_speech = new unsigned char[DESCRSTRING_SIZE] {};
  prototype->_content_id = sqlite3_column_int(statement, 1);
  prototype->_charge = sqlite3_column_int(statement, 2);
  tmp_name = sqlite3_column_text(statement, 3);
  for (size_t i = 0; i < NAMESTRING_SIZE && tmp_name[i] != '\0'; ++i) {
    prototype->_name[i] = tmp_name[i];
  }
  tmp_description = sqlite3_column_text(statement, 4);
  for(size_t i = 0; i < DESCRSTRING_SIZE && tmp_description[i] != '\0'; ++i) {
    prototype->_description[i] = tmp_description[i];
  }
  tmp_speech = sqlite3_column_text(statement, 5);
  for (size_t i = 0; i < DESCRSTRING_SIZE && tmp_speech[i] != '\0'; ++i) {
    prototype->_speech[i] = tmp_speech[i];
  }  
  delete[] tmp_name;
  delete[] tmp_description;
  delete[] tmp_speech;
  sqlite3_finalize(statement);
  return return_code;
}

int Forge::MakeEquipableItem(int query_id, int level, EquipableItem** spawned) {
  TEquipablePrototype prototype;
  int return_code = get_equipable_prototype(query_id, &prototype);
  EquipableItem* item = NULL;
  if (prototype._slots[ES_WEAPON1] || prototype._slots[ES_WEAPON2]) {
    if (prototype._distance > 0) {
      item = new RangedWeapon(prototype, prototype._name, prototype._manufacturer, level);
	} else {
      item = new MeleeWeapon(prototype, prototype._name, prototype._manufacturer, level);
	}
  }
  if (prototype._slots[ES_HEAD]) {
    item = new Head(prototype, prototype._name, prototype._manufacturer, level);
  }
  if (prototype._slots[ES_CHEST]) {
    item = new Chest(prototype, prototype._name, prototype._manufacturer, level);
  }
  if (prototype._slots[ES_HANDS]) {
    item = new Hands(prototype, prototype._name, prototype._manufacturer, level);
  }
  if (prototype._slots[ES_BOOTS]) {
    item = new Boots(prototype, prototype._name, prototype._manufacturer, level);
  }
  if (prototype._slots[ES_LEGS]) {
    item = new Legs(prototype, prototype._name, prototype._manufacturer, level);
  }
  if (prototype._slots[ES_TRINKET1] || prototype._slots[ES_TRINKET2] || prototype._slots[ES_TRINKET3] || prototype._slots[ES_TRINKET4]) {
    item = new Trinket(prototype, prototype._name, prototype._manufacturer, level);
  }
  *spawned = item;
  delete[] prototype._description;
  delete[] prototype._name;
  delete[] prototype._manufacturer;
  return return_code;
}

int Forge::MakeItem(int query_id, int level, Item** spawned) {
  EquipableItem* item = NULL;
  int response = MakeEquipableItem(query_id, level, &item);
  *spawned = item;
  return response;
}

int Forge::MakeTile(int query_id, LocalMapObject** spawned) {
  int response;
  LocalMapObject* tile = NULL;
  TTilePrototype prototype;
  response = get_tile_prototype(query_id, &prototype);
//  tile = new LocalMapObject(prototype);
  *spawned = tile;
  delete[] prototype._name;
  delete[] prototype._description;
  return response;
}

int Forge::MakeNPC(int query_id, int level, NPC** spawned) {
  int response;
  NPC* npc = NULL;
  TNPCPrototype prototype;
  response = get_npc_prototype(query_id, &prototype);
  if (prototype._charge != FREE_INDEX) {
    //npc = new QuestGiver(prototype, level);
  } else {
    if (prototype._charge == 3) {
      //npc = new BlackMarket(prototype, level);
	} else {
      if (prototype._content_id == 0) {
      //  npc = new WeaponTrader(prototype, level);
	  }
	  if (prototype._content_id == 5) {
        //npc = new ArmourTrader(prototype, level);
	  } else {
       // npc = new MunitionsTrader(prototype, level);
	  }
	}
  }
  *spawned = npc;
  delete[] prototype._name;
  delete[] prototype._description;
  delete[] prototype._speech;
  return response;
}


