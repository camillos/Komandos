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
    const int DefaultFrameLenght = 11;
    const int StartParamPoss = 3;

    void OnRunDllFrame(char * frame, int frameLenght);
    void OnStopDllFrame(char * frame, int frameLenght);
};

#endif // CMDEXECUTOR_H_INCLUDED
