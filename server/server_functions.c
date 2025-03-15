#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

struct AcceptedClient 
{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    boolean isAccepted;
};

unsigned char acceptedSocketsCount;
unsigned short won_games;
unsigned short lost_games;

struct WordElement
{
    char character;
    boolean isGuessed;
};

boolean bindAndListen(int *serverSocketFD, struct sockaddr_in **serverAddress) {
    int result = bind(*serverSocketFD, (struct sockaddr*)*serverAddress, sizeof(**serverAddress));
    
    if (result == FALSE) printf("Bind successful!\n");
    else {
        printf("Failed to bind. Error Code: %d\n", WSAGetLastError()); 
        return FALSE;
    }

    int listenResult = listen(*serverSocketFD, 10);
    
    if (listenResult == FALSE) printf("Listening...\n");
    else {
        printf("Failed to listen. Error Code: %d\n", WSAGetLastError());
        return FALSE;
    }

    return TRUE;
}

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

void wordToString(struct WordElement word[], char *wordString) {
    for (int i = 0; i < 5; i++) {
        if (word[i].isGuessed) wordString[i] = word[i].character;
        else wordString[i] = '_';
    }
    wordString[5] = '\0';
}

boolean sendAndRecv(struct AcceptedClient **pSocket, boolean *isLost, boolean *isWon, 
    struct WordElement word[], unsigned char *remaining_hp, char *received_character) {

    char *wordString = malloc(6 * sizeof(char));
    wordToString(word, wordString);
    printf("Word: %s\n", wordString);
        
    if (send((*pSocket)->acceptedSocketFD, (const char *)isLost, sizeof(*isLost), 0) == SOCKET_ERROR ||
        send((*pSocket)->acceptedSocketFD, (const char *)isWon, sizeof(*isWon), 0) == SOCKET_ERROR || 
        send((*pSocket)->acceptedSocketFD, (const char *)&acceptedSocketsCount, sizeof(acceptedSocketsCount), 0) == SOCKET_ERROR ||
        send((*pSocket)->acceptedSocketFD, (const char *)&won_games, sizeof(won_games), 0) == SOCKET_ERROR ||
        send((*pSocket)->acceptedSocketFD, (const char *)&lost_games, sizeof(lost_games), 0) == SOCKET_ERROR ||
        send((*pSocket)->acceptedSocketFD, (const char *)wordString, 6 * sizeof(char), 0) == SOCKET_ERROR ||
        send((*pSocket)->acceptedSocketFD, (const char *)remaining_hp, sizeof(*remaining_hp), 0) == SOCKET_ERROR)
    {
        printf("Client disconnected. Closing socket.\n");
        closesocket((*pSocket)->acceptedSocketFD);
        free(wordString);
        *pSocket = NULL;
        --acceptedSocketsCount;
        return FALSE;
    }
    
    free(wordString);

    int recvResult = recv((*pSocket)->acceptedSocketFD, received_character, sizeof(*received_character), 0);
    
    if (recvResult <= 0) {
        printf("Client disconnected. Closing socket.\n");
        closesocket((*pSocket)->acceptedSocketFD);
        --acceptedSocketsCount;
        *pSocket = NULL;
        return FALSE;
    }

    return TRUE;
}