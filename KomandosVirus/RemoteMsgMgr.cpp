#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#include "RemoteMsgMgr.h"
#include "Exception.h"


#include <iostream>

DWORD WINAPI Listenig(LPVOID lpParam)
{
    RemoteMsgMgr *msgMgr = ((RemoteMsgMgr*)lpParam);
    try
    {
        msgMgr->Listen();
    }
    catch(Exception e)
    {
        std::cout << e.msg << std::endl;
    }

    return 0;
}

RemoteMsgMgr::RemoteMsgMgr(CmdExecutor *cmdExecutor)
{
    this->DefaultPort = 6666;
    this->cmdExe = cmdExecutor;
    this->isListening = false;

    this->receiveBuffer = new char[receiveBufferLength];
}

RemoteMsgMgr::~RemoteMsgMgr()
{
    delete [] receiveBuffer;
}

void RemoteMsgMgr::Listen()
{
    if(isListening)
        throw Exception("RemoteMsgMgr jest juz w trybie nasluchu.");

    canRun = true;
    isListening = true;

    if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        throw Exception("Blad WSAStartup. Kod bledu: " + WSAGetLastError());

    if((s = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
        throw Exception("Nie mozna utworzyc soketu. Kod bledu: " + WSAGetLastError());

    serverSocket.sin_family = AF_INET;
    serverSocket.sin_addr.s_addr = INADDR_ANY;
    serverSocket.sin_port = htons(DefaultPort);

    // dla broadcastu
    int options = 1;
    if ((setsockopt(s, SOL_SOCKET, SO_BROADCAST,(char *)&options,sizeof(options))) < 0){
        throw Exception("Nie mozna sluchac broadcastu. Kod bledu: " + WSAGetLastError());
    }

    if(bind(s ,(struct sockaddr *)&serverSocket , sizeof(serverSocket)) == SOCKET_ERROR)
        throw Exception("Blad w trakcie bindowania. Kod bledu: " + WSAGetLastError());

    struct sockaddr_in clientSocket2;

    int recv_len = 0;
    int clientSocketLength = (int)sizeof(clientSocket2);

    while(canRun)
    {

        if((recv_len = recvfrom(s, receiveBuffer, receiveBufferLength, 0, (struct sockaddr *) &clientSocket2, &clientSocketLength)) == SOCKET_ERROR)
        {
            //std::stringstream s;
            //s << WSAGetLastError();
            throw Exception("Blad w trakcie odbierania datagramow. Kod bledu: " + WSAGetLastError());
            //throw Exception(s.str());
        }

        if(recv_len <= 0) continue;

        char* frame = new char[recv_len];

        for(int i = 0;i < recv_len; i++)
            frame[i] = receiveBuffer[i];

        std::string client_ip = inet_ntoa(clientSocket.sin_addr);
        int replay_lenght = cmdExe->Execute(frame, recv_len, client_ip);

        if(replay_lenght > 0)
        {
            if (sendto(s, frame, replay_lenght, 0, (struct sockaddr*) &clientSocket2, clientSocketLength) == SOCKET_ERROR)
            {
                delete[] frame;
                throw Exception("Blad w trakcje wysylania odpowiedzi na komunikat. Kod bledu: " + WSAGetLastError());
            }
        }

        delete [] frame;
    }

    isListening = false;

}

void RemoteMsgMgr::Clean()
{
    WSACleanup();
    canRun = false;
    isListening = false;

    WaitForMultipleObjects(1, &ThreadHandle, TRUE, INFINITE);
    CloseHandle(ThreadHandle);
}

void RemoteMsgMgr::StartListen()
{
    ThreadHandle = CreateThread( NULL, 0, Listenig, this, 0, NULL);
}

void RemoteMsgMgr::StopListen()
{
    canRun = false;
    while(isListening){}

    closesocket(s);
    WSACleanup();

    WaitForMultipleObjects(1, &ThreadHandle, TRUE, INFINITE);
    CloseHandle(ThreadHandle);
}
