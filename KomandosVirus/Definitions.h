#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

#include <windows.h>

enum STATE
{
    WORK,
    NOWORK
};

class CMD_KEY
{
public:
    static char ExecuteDll;
    static char BreakExecuteDll;
    static char ReciveDll;
    static char BreakReciveDll;
    static char SendOutDll;
    static char BreakSendOutDll;
    static char CheckForDll;
    static char CheckForDllReplay;

    static char Error;
};



//const int FrameLenght = 11;

#endif // DEFINITIONS_H_INCLUDED
