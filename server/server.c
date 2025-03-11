#include <windows.h>

#include "../common/common.h"
#include "server_functions.h"

struct AcceptedClient 
{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    boolean isAccepted;
};

unsigned char players = 0;
unsigned short won_games = 0;
unsigned short lost_games = 0;

void exchangeDataWithClient(int socketFD);
void acceptingConnections(int serverSocketFD);

int main() {
    
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    int serverSocketFD = createTCPIPv4Socket();
    struct sockaddr_in *serverAddress = createIPv4Adress("", 2000);

    int result = bind(serverSocketFD, (struct sockaddr*)serverAddress, sizeof(*serverAddress));
    if (result == 0) printf("Bind successful!\n");
    else {printf("Failed to bind. Error Code: %d\n", WSAGetLastError()); return 1;}

    int listenResult = listen(serverSocketFD, 10);
    if (listenResult == 0) printf("Listening...\n");
    else {printf("Failed to listen. Error Code: %d\n", WSAGetLastError()); return 1;}

    struct AcceptedClient *clientSocket = acceptIncomingConnection(serverSocketFD);

    acceptingConnections(serverSocketFD);

    exchangeDataWithClient(clientSocket);

    closesocket(clientSocket->acceptedSocketFD);
    closesocket(serverSocketFD);
    WSACleanup();
    return 0;
}

void acceptingConnections(int serverSocketFD) {
    HANDLE thread; //TODO multithreading

    struct AcceptedClient *clientSocket = acceptIncomingConnection(serverSocketFD);

}

void exchangeDataWithClient(int socketFD) {
    while (1) {
        send(socketFD, (const char *)&players, sizeof(players), 0);
        send(socketFD, (const char *)&won_games, sizeof(won_games), 0);
        send(socketFD, (const char *)&lost_games, sizeof(lost_games), 0);  

        char received_character;
        recv(socketFD, &received_character, sizeof(received_character), 0);
        printf("Received character: %c\n", received_character);
    }
}