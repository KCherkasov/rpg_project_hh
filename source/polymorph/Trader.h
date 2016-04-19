#include "NPC.h"
#include "prototypes.h"

class Trader: NPC {
  public:
    Trader(): NPC() {}
    virtual ~Trader() {}

  protected:
    int _charge;
    virtual int form_asortment(TNPCPrototype &prototype, int level) = 0;
};
