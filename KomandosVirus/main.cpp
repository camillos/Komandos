#include <iostream>
#include <windows.h>

#include "Replicator.h"
#include "TaskMgr.h"

using namespace std;

int main()
{
    Replicator *replicator = new Replicator();
    STATE state = replicator->Start();

    if(state == NOWORK)
    {
        //delete replicator;
        //return 0;
    }

    TaskMgr *taskMgr = new TaskMgr();



    system("pause");

    delete taskMgr;
    delete replicator;
    return 0;
}
