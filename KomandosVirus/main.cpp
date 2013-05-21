#include <iostream>
#include <windows.h>

using namespace std;


typedef void( * MYPROC )( const LPCSTR );
MYPROC ShowFromDll;


int main()
{
    cout << "Hello world!" << endl;
    HINSTANCE hDll;
    hDll = LoadLibrary("KomandosTask");

    if( hDll != NULL )
    {
        // je�li wszystko posz�o dobrze, tutaj mo�emy wywo�a� jak�� funkcj� biblioteczn�
        cout << "Wczytano dll.." << endl;

        ShowFromDll =( MYPROC ) GetProcAddress( hDll, "SomeFunction" );
        if( ShowFromDll != NULL )
        {
            cout << "znaleziono" << endl;
            (ShowFromDll)("Dziala dll");
        }

        FreeLibrary( hDll );
    }

    return 0;
}
