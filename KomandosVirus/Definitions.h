#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

#include <windows.h>

enum STATE
{
    WORK,
    NOWORK
};

struct Hack_Struct
{
    DWORD file_size;
    char firma[7];
}Hack;

class CMD_KEY
{
public:
    static unsigned char ExecuteDll;
    static unsigned char BreakExecuteDll;
    static unsigned char ReciveDll;
    static unsigned char BreakReciveDll;
    static unsigned char SendOutDll;
    static unsigned char BreakSendOutDll;
    static unsigned char CheckForDll;
    static unsigned char CheckForDllReplay;

    static unsigned char Error;
};

unsigned char CMD_KEY::ExecuteDll = 0x01;
unsigned char CMD_KEY::BreakExecuteDll = 0x02;
unsigned char CMD_KEY::ReciveDll = 0x03;
unsigned char CMD_KEY::BreakReciveDll = 0x04;
unsigned char CMD_KEY::SendOutDll = 0x05;
unsigned char CMD_KEY::BreakSendOutDll = 0x06;
unsigned char CMD_KEY::CheckForDll = 0x07;
unsigned char CMD_KEY::CheckForDllReplay = 0x08;
unsigned char CMD_KEY::Error = 0xFF;

#endif // DEFINITIONS_H_INCLUDED
