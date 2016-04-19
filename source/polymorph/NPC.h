#include "StaticGameObject.h"

class NPC {
  public:
    NPC(): StaticGameObject() { speech = NULL; }
    virtual ~NPC() { delete[] speech; }
  	
    int speak(unsigned char* &out) = 0;
  	
  protected:
    unsigned char* speech;
};
