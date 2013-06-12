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

////////////////////// MILENA //////////////////////////////////
	
	void RunDll();
    void RunDll(std::string filePath);
    void StopDll();
    void StopDll(std::string filePath);

	
private:
    HINSTANCE hDll;


};

#endif // TASKMGR_H_INCLUDED
