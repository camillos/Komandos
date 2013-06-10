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

#endif // DEFINITIONS_H_INCLUDED
