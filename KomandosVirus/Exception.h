#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#include <string>
using namespace std;

class Exception
{
public:
    Exception();
    Exception(string message);
    void SetMessage(string message);
    string GetMessage();

//private:
    string msg;
};


#endif // EXCEPTION_H_INCLUDED
