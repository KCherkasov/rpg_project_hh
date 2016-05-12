#include "PartyMember.h"

PartyMember::PartyMember(TPartyMemberPrototype &prototype, unsigned char* name, int level): AliveGameObject() {
  srand(static_cast<unsigned int>(time(0)));
  for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
    _name[i] = name[i];
  }
  _damage = new int[PAIR_ARR_SIZE] {0};
  _exp = new int[PAIR_ARR_SIZE] {0};
  _health = new int[PAIR_ARR_SIZE] {0};
  _stats = new int[CS_SIZE] {0};
  _killed_count = 0;
  _money_earned = 0;
  _salary = prototype._salary;
  _initiative = prototype._initiative;
  _exp[MAXIMAL_VALUE_INDEX] = FIRST_LEVELUP_CAP;
  _level = START_LEVEL;
  _health[MAXIMAL_VALUE_INDEX] = prototype._health;
  _health[CURRENT_VALUE_INDEX] = _health[MAXIMMAL_VALUE_INDEX];
  for (size_t i = 0; i < CS_SIZE; ++i) {
    _stats[i] = prototype._stats[i];
  }
  _equipped = new Equipped();
  _unpaid_count = 0;
  _gender = prototype._gender;
  if (_level > START_LEVEL) {
    for (size_t  i = 0; i < _level; ++i) {
      for(size_t j = 0; j < CS_SIZE; ++j) {
        _stats[i] += STAT_UP_PER_LEVEL;
        _skill_points += POINTS_PER_LEVEL;
	  }
	  double tmp = _exp[MAXIMAL_VALUE_INDEX];
	  tmp *= EXP_RAISE;
	  _exp[CURRENT_VALUE_INDEX] = _exp[MAXIMAL_VALUE_INDEX];
	  _exp[MAXIMAL_VALUE_INDEX] = round(tmp);
	}
	while(_skill_points > 0) {
      int rnd_index = rand() % CS_SIZE;
      ++_stats[rnd_index];
      --_skill_points;
	}
  }
}

PartyMember::~PartyMember() {
  delete[] _damage;
  delete[] _exp;
  delete[] _health;
  delete[] _stats;
  delete _equipped;
}

int PartyMember::get_stat(int index, int &result) {
  if (index < 0 || index >= CS_SIZE) {
    return 0;
  }
  result = _stats[index];
  return 0;
}

int* PartyMember::get_stats() {
  int* result = new int[CS_SIZE];
  for (size_t i = 0; i < CS_SIZE; ++i) {
    result[i] = _stats[i];
  }
  return result;
}

int PartyMember::change_stat(int index, int value) {
  if (_skill_points > 0) {
    if (index > FREE_INDEX && index < CS_SIZE) {
      _stats[index] += value;
      --_skill_points;
	}
  }	
  return 0;
}

int PartyMember::change_exp(int value) {
  _exp[CURRENT_VALUE_INDEX] += value;
  return 0;
}

int PartyMember::change_money_earned(int value) {
  _money_earned += value;
  return 0;
}

int PartyMember::change_killed_count() {
  ++_killed_count;
  return 0;
}

int PartyMember::level_up() {
  if (_exp[CURRENT_VALUE_INDEX] >= _exp[MAXIMAL_VALUE_INDEX]) {
  	++_level;
  	double tmp = _exp[MAXIMAL_VALUE_INDEX];
  	tmp *= EXP_RAISE;
  	_exp[MAXIMAL_VALUE_INDEX] = round(tmp);
    _skill_point += POINTS_PER_LEVEL;
    for (size_t i = 0; i < CS_SIZE; ++i) {
      _stats[i] += STAT_UP_PER_LEVEL;
	}
	if (_salary / PERCENT_MOD_CAP == 0) {
      _salary += _salary / 5;
	} else {
      _salary += _salary / PERCENT_MOD_CAP;
	}
  }
  return 0;
}

int PartyMember::what(std::string &out) {
  out.clear();
  std::string stat_names[CS_SIZE] {"accuracy: ","reaction: ","strength: ","toughness: ","awareness: ","intelligence: ","persuasion: ","speed: "};
  std::string str;
  str.clear();
  char* digit = new char[NAMESTRING_SIZE / 2];
  str.append((char*) _name);
  str.append("\t level: ");
  str.append(itoa(_level, digit, 10));
  str.append("\n--\n");
  str.append("health: ");
  str.append(itoa(_health[CURRENT_VALUE_INDEX], digit, 10));
  str.append("/");
  str.append(itoa(_health[MAXIMAL_VALUE_INDEX], digit, 10));
  str.append("\n");
  str.append("experience: ");
  str.append(itoa(_exp[CURRENT_VALUE_INDEX], digit, 10));
  str.append("/");
  str.append(itoa(_exp[MAXIMAL_VALUE_INDEX], digit, 10));
  str.append("\n");
  str.append("Free skill points: ");
  str.append(itoa(_skill_points, digits, 10));
  str.append("\n");
  str.append("Stats:\n");
  for (size_t i = 0; i <  CS_SIZE; ++i) {
    str += stat_names[i];
    str.append(itoa(_stats[i], digit, 10));
    str.append(";\n");
  }
  str.append("killed: ");
  str.append(itoa(_killed_count, digit, 10));
  str.append("\n");
  str.append("salary: ");
  str.append(itoa(_salary, digit, 10));
  str.append("\n");
  str.append("total earnings: ");
  str.append(itoa(_money_earned));
  str.append("\n");
  out += str;
  delete[] digit;
  return 0;
}

int PartyMember::get_pic_name(std::string &out) {
  out.clear();
  std::string male_pic_prefix;
  std::string female_pic_prefix;
  std::string exec;
  male_pic_prefix = "face_male_";
  female_pic_prefix = "face_female_";
  exec = ".png";
  char* digit = new char[NAMESTRING_SIZE / 3];
  if (_gender) {
    out += male_pic_prefix;
  } else {
    out += female_pic_prefix;
  }
  out.append(itoa(_pic_id, digit, 10));
  out += exec;
  delete[] digit;
  return 0;
}
