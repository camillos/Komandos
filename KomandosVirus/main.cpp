#include <iostream>

#include "Replicator.h"
using namespace std;

int main()
{
    Replicator *replicator = new Replicator();
    STATE state = replicator->Start();

    if(state == NOWORK)
    {
        delete replicator;
        return 0;
    }





    delete replicator;
    return 0;
}
