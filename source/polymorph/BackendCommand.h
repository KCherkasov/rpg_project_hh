#include "Command.h"
#include "GameObject.h"

class BackendCommand: public Command {
  public:
    BackendCommand(GameObject** sender, GameObject** target): _sender(*sender), _target(*target) {}
    virtual BackendCommand() { _sender = NULL; _target = NULL; }
  protected:
    GameObject* _sender;
    GameObject* _target;
};
