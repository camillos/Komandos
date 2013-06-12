#ifndef REMOTEMSGMGR_H_INCLUDED
#define REMOTEMSGMGR_H_INCLUDED

#include <windows.h>
#include <winsock2.h>
#include <string>

#include "CmdExecutor.h"

DWORD WINAPI Listenig(LPVOID lpParam);

class RemoteMsgMgr
{
public:
    RemoteMsgMgr(CmdExecutor *cmdExecutor);
    ~RemoteMsgMgr();
    void StartListen();
    void StopListen();
    void Listen();
    void Send(std::string ip, char* frame);
    void Replay(char* frame);
    void Broadcast(char* frame);
    void Clean();

private:
    CmdExecutor *cmdExe;
    int DefaultPort;

    volatile bool isListening;
    volatile bool canRun;

    SOCKET s;
    struct sockaddr_in serverSocket, clientSocket;
    WSADATA wsa;

    char *receiveBuffer;
    const int receiveBufferLength = 1024;

    HANDLE ThreadHandle;

};


#endif // REMOTEMSGMGR_H_INCLUDED
