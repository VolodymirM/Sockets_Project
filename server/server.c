#include "../common/common.h"
#include "server_functions.h"

struct AcceptedClient 
{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    boolean isAccepted;
};

struct AcceptedClient acceptedSockets[10] ;
int acceptedSocketsCount = 0;

void acceptingConnections(int serverSocketFD) {
    while (1) {
        struct AcceptedClient* clientSocket = acceptIncomingConnection(serverSocketFD);
        if (clientSocket == NULL) {
            continue;
        }
        acceptedSockets[acceptedSocketsCount++] = *clientSocket;

        CreateThread(NULL, 0, exchangeDataWithClient, clientSocket, 0, NULL);
    }
}

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

    acceptingConnections(serverSocketFD);

    closesocket(serverSocketFD);
    WSACleanup();
    return 0;
}