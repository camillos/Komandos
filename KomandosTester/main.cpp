#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 6666   //The port on which to listen for incoming data
#define SERVER "127.0.0.1"  //ip address of udp server

using namespace std;

int main()
{
    struct sockaddr_in connectedSocket;

int s;
int length=sizeof(connectedSocket);

char receiveBuffer[1000];
char message[11] = {};

//clear the buffer by filling null, it might have previously received data
memset(receiveBuffer,'\0', 1000);

WSADATA wsa;
//Initialise winsock
printf("\nInitialising Winsock...\n");
if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
{
    printf("\nFailed. Error Code : %d",WSAGetLastError());
    exit(EXIT_FAILURE);
}
printf("\n.........Initialised.\n");


//create socket
if ( (s=socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR)
{
    printf("\n\nsocket() failed with error code : %d" , WSAGetLastError());
    exit(EXIT_FAILURE);
}


//setup address structure
memset((char *) &connectedSocket, 0, sizeof(connectedSocket));
connectedSocket.sin_family = AF_INET;
connectedSocket.sin_port = htons(PORT);
 //connectedSocket.sin_port = INADDR_BROADCAST;
//connectedSocket.sin_addr.S_un.S_addr = inet_addr(SERVER);
connectedSocket.sin_addr.s_addr = INADDR_BROADCAST;

int options = 1;
if ((setsockopt(s, SOL_SOCKET, SO_BROADCAST,(char *)&options,sizeof(options))) < 0){
    printf("%d",WSAGetLastError());
}


while(1)
{
    printf("\n\n\nWybierz zadanie: ");
    printf("\n[1] Wykonaj Dll");
    printf("\n[2] Zatrzymaj Dll");
    printf("\n\nWybor: ");

    char wybor;
    cin >> wybor;

    if(wybor == '1')
    {
        message[0] = 'K';
        message[1] = 'V';
        message[2] = 0x01;
        //params
        message[3] = 0x00;
        message[4] = 0x00;
        message[5] = 0x00;
        message[6] = 0x00;
        message[7] = 0x00;
        message[8] = 0x00;
        message[9] = 0x00;
        message[10] = 0x00;
    }

    if(wybor == '2')
    {
        message[0] = 'K';
        message[1] = 'V';
        message[2] = 0x02;
        //params
        message[3] = 0x00;
        message[4] = 0x00;
        message[5] = 0x00;
        message[6] = 0x00;
        message[7] = 0x00;
        message[8] = 0x00;
        message[9] = 0x00;
        message[10] = 0x00;
    }


    //gets(message);

  //send the message
    if (sendto(s, message, 11 , 0 , (struct sockaddr *) &connectedSocket, sizeof(connectedSocket)) == SOCKET_ERROR)
    {
        printf("\nsendto() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

        printf("\nMessage Successfully sent to Server");
      // fflush(stdout);

    if (recvfrom(s, receiveBuffer, 1000, 0, (struct sockaddr *) &connectedSocket,&length) == SOCKET_ERROR)
    {
       printf("\nrecvfrom() failed with error code : %d" , WSAGetLastError());
       exit(EXIT_FAILURE);
    }

    printf("\nServer Says : ");
    printf(receiveBuffer,sizeof(receiveBuffer));

}

closesocket(s);
WSACleanup();













    return 0;
}
