#ifndef TASKMGR_H_INCLUDED
#define TASKMGR_H_INCLUDED

DWORD WINAPI sendDLL(LPVOID lpParam);
DWORD WINAPI listenForDLL(LPVOID lpParam);

class TaskMgr
{

public:
    int port;



    TaskMgr();

    void StartSendDLL();
    void StopSendDLL();
    void StartListenForDLL();
    void StopListenForDLL();


};

#endif // TASKMGR_H_INCLUDED
