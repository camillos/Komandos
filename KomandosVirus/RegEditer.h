#ifndef REGEDITER_H_INCLUDED
#define REGEDITER_H_INCLUDED

#include <string>

class RegEditer
{
public:
    void Register();
    bool IsMainCopy();
    bool IsRegistered();
    char* GetMyName();

private:
    std::string getMyPath();
    std::string getMyLongPath();
};

#endif // REGEDITER_H_INCLUDED
