#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <malloc.h>

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