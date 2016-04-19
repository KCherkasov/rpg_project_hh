#pragma once

namespace generic_consts {

  const int  EMPTY_STACK = 0;
  
  const int FREE_INDEX = -1;

  const int MIN_COLLECTABLE_STACK = 1;
  const int MAX_COLLECTABLE_STACK = 200;

  const int MIN_CONSUMABLE_STACK = 1;
  const int MAX_CONSUMABLE_STACK = 200;

  const int OK_CODE = 0;
  const int SOME_ERROR_CODE = 1;

  const int START_LEVEL = 1;
  const int MAX_LEVEL = 70;
  const int POINTS_PER_LEVEL = 5;
  
  const int STAT_RAISE_PER_LEVEL = 1;
  const int DAMDEF_RAISE_PER_LEVEL = 5;
  const int HP_RAISE_PER_LEVEL = 8;
  const int COST_RAISE_PER_LEVEL = 5;

  const int NAMESTRING_SIZE = 31;
  const int DESCRSTRING_SIZE = 301;
  
  const double MANUFACTURER_BONUS = 1.15;
  const int MANUFACTURERS_COUNT = 10;
  const int NAMES_COUNT = 10;
  
  const int PERCENT_CAP = 100;

  enum TCharStats { CS_ACCURACY, CS_REACTION, CS_STRENGTH, CS_TOUGHNESS, CS_AWARENESS, CS_INTELLIGENCE, CS_PERSUASION, CS_SPEED, CS_SIZE };
  enum TEquipmentSlot { ES_HEAD, ES_CHEST, ES_HANDS, ES_BOOTS, ES_LEGS, ES_TRINKET1, ES_TRINKET2, ES_TRINKET3, ES_TRINKET4, ES_WEAPON1, ES_WEAPON2, ES_SIZE };
  enum TEquipmentKind { EK_PISTOL, EK_SMG, EK_ASSAULT_RIFLE, EK_SNIPER_RIFLE, EK_MELEE, EK_LIGHT, EK_MEDIUM, EK_HEAVY, EK_TRINKET, EK_SIZE};

}

