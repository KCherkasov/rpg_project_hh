#include "Squad.h"

Squad::Squad() {
  _members.clear();
  _pack_id = FREE_INDEX;
}

Squad::Squad(int pack_id) {
	_members.clear();
	_pack_id = pack_id;
}

Squad::~Squad() {
  for (size_t i = 0; i < _members.size(); ++i) {
  	delete _members[i];
  }
  _members.clear();
}

int Squad::get_member_address(AliveGameObject* &result, int to_find) {
  delete result;
  result = NULL;
  if (to_find > FREE_INDEX && to_find < _members.size()) {
    result = _members[to_find];
  }
  return 0;
}

int Squad::get_member_index(AliveGameObject* &to_find, int &result) {
  result = FREE_INDEX;
  if (to_find != NULL) {
    for (size_t i = 0; i < _members.size(); ++i) {
      if (_members[i] == to_find) {
        result = i;
        break;
	  }
	}
  }
  return 0;
}
