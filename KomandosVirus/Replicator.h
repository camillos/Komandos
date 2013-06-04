#ifndef REPLICATOR_H_INCLUDED
#define REPLICATOR_H_INCLUDED

#include "Definitions.h"

class Replicator
{
private:
    bool IsMainCopy();


public:
    Replicator();
    STATE Start();
    void Infect();

};

#endif // REPLICATOR_H_INCLUDED
