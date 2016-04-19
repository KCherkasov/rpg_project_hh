#include "NPC.h"
#include "prototypes.h"

class QuestGiver : NPC {
  public:
    QuestGiver();
    QuestGiver(TNPCPrototype &prototype);
    virtual ~QuestGiver();
    
    int get_quest_id() { return _quest_id; }
    int speak(unsigned char* &out);
    int what(std::string &out);

  protected:
    int _quest_id;
};
