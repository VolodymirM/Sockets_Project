#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>

unsigned char players = 0;
unsigned short won_games = 0;
unsigned short lost_games = 0;

struct AcceptedClient 
{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    boolean isAccepted;
};

struct AcceptedClient * acceptIncomingConnection(int serverSocketFD) {
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);

    int clientSocketFD = accept(serverSocketFD, (struct sockaddr *)&clientAddress, &clientAddressSize);
    
    struct AcceptedClient *acceptedClient = malloc(sizeof(struct AcceptedClient));
    acceptedClient->acceptedSocketFD = clientSocketFD;
    acceptedClient->address = clientAddress;
    acceptedClient->error = WSAGetLastError();
    acceptedClient->isAccepted = (clientSocketFD > 0);
    
    if (!acceptedClient->isAccepted)
        acceptedClient->error = clientSocketFD;

    return acceptedClient;
}

DWORD WINAPI exchangeDataWithClient(LPVOID lpParam) {
    struct AcceptedClient *pSocket = (struct AcceptedClient *)lpParam;

    while (1) {
        if (send(pSocket->acceptedSocketFD, (const char *)&players, sizeof(players), 0) == SOCKET_ERROR ||
            send(pSocket->acceptedSocketFD, (const char *)&won_games, sizeof(won_games), 0) == SOCKET_ERROR ||
            send(pSocket->acceptedSocketFD, (const char *)&lost_games, sizeof(lost_games), 0) == SOCKET_ERROR) {
            printf("Client disconnected. Closing socket.\n");
            closesocket(pSocket->acceptedSocketFD);
            return 0;
        }

        char received_character;
        int recvResult = recv(pSocket->acceptedSocketFD, &received_character, sizeof(received_character), 0);
        
        if (recvResult <= 0) {
            printf("Client disconnected. Closing socket.\n");
            closesocket(pSocket->acceptedSocketFD);
            return 0;
        }
        printf("Received character: %c\n", received_character);
    }
}