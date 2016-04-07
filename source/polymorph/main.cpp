#include "Forge.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>

int main(int argc, char** argv) {
  srand(static_cast<unsigned int>(time(0)));
  int rnd = rand() % 10 + 1;
  Item* item = NULL;
  std::string db_name;
  db_name = "classic.db";
  Forge* forge = new Forge((char*)db_name.c_str());
  for (size_t i = 0; i < rnd; ++i) {
    int code = forge->MakeItem(1, rand() % 40 + START_LEVEL, item);
    char* response;
    response = item->what();
    printf(response);
    delete response;
    delete item;
  }
  delete forge;
  int key;
  scanf("%d", &key);
  return 0;
}
