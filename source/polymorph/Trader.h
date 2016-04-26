#pragma once

#ifndef TRADER_H
#define TRADER_H

#include "NPC.h"
#include "prototypes.h"

class Trader: public NPC {
  public:
    Trader(): NPC() {}
    virtual ~Trader() {}

  protected:
    int _charge;
    virtual int form_asortment(TNPCPrototype &prototype, int level) = 0;
};

#endif
