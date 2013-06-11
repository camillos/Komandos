#ifndef REMOTEMSGMGR_H_INCLUDED
#define REMOTEMSGMGR_H_INCLUDED

#include <winsock2.h>
#include <string>

#include "CmdExecutor.h"

class RemoteMsgMgr
{
public:
    RemoteMsgMgr(CmdExecutor *cmdExecutor);
    ~RemoteMsgMgr();
    void StartListen();
    void StopListen();
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
    const int receiveBufferLength = 16;

};


#endif // REMOTEMSGMGR_H_INCLUDED
