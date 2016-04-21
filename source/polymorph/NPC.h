#pragma once

#ifndef NPC_H
#define NPC_H

#include "StaticGameObject.h"

class NPC: StaticGameObject {
  public:
    NPC(): StaticGameObject() { speech = NULL; }
    virtual ~NPC() { delete[] speech; }
  	
    virtual int speak(unsigned char* &out) = 0;
  	
  protected:
    unsigned char* speech;
};

#endif
