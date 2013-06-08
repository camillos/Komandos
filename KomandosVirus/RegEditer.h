#ifndef REGEDITER_H_INCLUDED
#define REGEDITER_H_INCLUDED

#include <string>
#include <windows.h>

class RegEditer
{
public:
    void Register();
    bool IsMainCopy();
    bool IsRegistered();

private:
    std::string getMyPath();
    std::string getMyLongPath();
};

#endif // REGEDITER_H_INCLUDED
