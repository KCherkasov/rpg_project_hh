#include "PartyMember.h"


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
