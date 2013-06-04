#include "Replicator.h"
#include <iostream>
#include <windows.h>

using namespace std;

Replicator::Replicator()
{

}

//Probuje wystarotwac replikacje
// jesli sie uda oznacza to ze jest jest glowna kopia wirusa
// jesli nie to ta kopia powstala w wyniku zarazenia i czeka na nowa ofiare
STATE Replicator::Start()
{
    if(!IsMainCopy()) return NOWORK;



    return WORK;
}

void Replicator::Infect()
{

}


bool Replicator::IsMainCopy()
{
    HKEY key;
    // otwarcie klucza
    if (RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\RegisteredApplications\\"), &key) != ERROR_SUCCESS)
    {
        cout << "Unable to open registry key" << endl;
    }

    // sprawdzenie czy klucz istnieje
    char value[256];
    DWORD value_length = 256;
    DWORD type = REG_SZ;

    if (RegQueryValueEx(key, TEXT("Komandos"), 0, &type, (LPBYTE)&value, &value_length) == ERROR_FILE_NOT_FOUND)
    {
        cout << "Unable to read registry key" << endl;
    }

    if(value[0] == '1')
    {
        cout << "This is not main copy" << endl;
        RegCloseKey(key);
        return false;

    }

    // dodanie klucza
    if (RegSetValueEx(key, TEXT("Komandos"), 0, REG_SZ, (LPBYTE)"1", strlen("1")*sizeof(char)) != ERROR_SUCCESS)
    {
        RegCloseKey(key);

        cout <<"Unable to set registry value value_name";
        return false;
    }
    else
    {
        cout << "Registered!" << endl;
    }

    RegCloseKey(key);

    return true;
}
