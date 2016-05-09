#pragma once

#ifndef TRADER_H
#define TRADER_H

#include "NPC.h"
#include "prototypes.h"

class Trader: public NPC {
  public:
    Trader(): NPC() {}
    virtual ~Trader() {}

    int get_charge() { return _charge; }
    int what(std::string &out) { return 0; }
    int speak(unsigned char* &out) { return 0; }
  protected:
    int _charge;
    virtual int form_assortment(TNPCPrototype &prototype, int level) = 0;
};

#endif
