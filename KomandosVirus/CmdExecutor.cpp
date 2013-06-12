#include "CmdExecutor.h"
#include "Definitions.h"

CmdExecutor::CmdExecutor(TaskMgr *taskMgr)
{
    this->taskMgr = taskMgr;
}

int CmdExecutor::Execute(char* frame, int frameLength, std::string clientIp)
{
    //gdy ramka nie ma odpowiedniej dlugosci
    if(frameLength < DefaultFrameLenght) return 0;

    //gdy ramka nie zaczyna sie odpowiednia sygnatura
    if(frame[0] != 'K' || frame[1] != 'V') return 0;

    int resultFrameLenght = 0;

    switch(frame[2])
    {
    case 0x01:
        this->OnRunDllFrame(frame, frameLength);
        break;

    case 0x02:
        this->OnStopDllFrame(frame, frameLength);
        break;

    case 0x03:
        break;

    case 0x04:
        break;

    case 0x05:
        break;

    case 0x06:
        break;

    case 0x07:
        break;

    case 0x08:
        break;

    case 0xFF:
        break;

    default:
        break;
    }

    return resultFrameLenght;
}


void CmdExecutor::OnRunDllFrame(char * frame, int frameLenght)
{
    for(int i = StartParamPoss; i < frameLenght; i++)
    {
        if(frame[i] != 0) return;
    }

    taskMgr->RunDll();
}

void CmdExecutor::OnStopDllFrame(char * frame, int frameLenght)
{
    for(int i = StartParamPoss; i < frameLenght; i++)
    {
        if(frame[i] != 0) return;
    }

    taskMgr->StopDll();
}

