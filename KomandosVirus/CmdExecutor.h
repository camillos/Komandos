#ifndef CMDEXECUTOR_H_INCLUDED
#define CMDEXECUTOR_H_INCLUDED

#include <string>

#include "TaskMgr.h"

class CmdExecutor
{
public:
    CmdExecutor(TaskMgr *taskMgr);

    // zwraca wartosc > 0 jesli nalezy odeslac odpowiedz,
    // w takim przypadku do frame zostanie wpisana ramka do wyslania
    int Execute(char* frame, int frameLength, std::string clientIp);

private:
    TaskMgr *taskMgr;
};

#endif // CMDEXECUTOR_H_INCLUDED
