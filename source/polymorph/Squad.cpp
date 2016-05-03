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
