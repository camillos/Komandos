#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#include "RemoteMsgMgr.h"
#include "Exception.h"


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

void RemoteMsgMgr::StartListen()
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

    if(bind(s ,(struct sockaddr *)&serverSocket , sizeof(serverSocket)) == SOCKET_ERROR)
        throw Exception("Blad w trakcie bindowania. Kod bledu: " + WSAGetLastError());

    int recv_len = 0;
    int clientSocketLength = sizeof(clientSocket);

    while(canRun)
    {
        if((recv_len = recvfrom(s, receiveBuffer, receiveBufferLength, 0, (struct sockaddr *) &clientSocket, &clientSocketLength)) == SOCKET_ERROR)
            throw Exception("Blad w trakcie odbierania datagramow. Kod bledu: " + WSAGetLastError());

        if(recv_len <= 0) continue;

        char* frame = new char[recv_len];

        for(int i = 0;i < recv_len; i++)
            frame[i] = receiveBuffer[i];

        std::string client_ip = inet_ntoa(clientSocket.sin_addr);
        int replay_lenght = cmdExe->Execute(frame, recv_len, client_ip);

        if(replay_lenght > 0)
        {
            // w replay_lenght mamy dlugosc ramki
            // w frame mamy ramke do odeslania

            //if (sendto(s, receiveBuffer, recv_len, 0, (struct sockaddr*) &clientSocket, clientSocketLength) == SOCKET_ERROR)
            //{
            //    printf("\nsendto() failed with error code : %d" , WSAGetLastError());
            //    // exit(EXIT_FAILURE);
            //    while(1);
            //}
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
}

void RemoteMsgMgr::StopListen()
{
    canRun = false;
    while(isListening){}

    closesocket(s);
    WSACleanup();
}
