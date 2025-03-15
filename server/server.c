#include "../common/common.h"
#include "server_functions.h"

#define MAX_PLAYERS 10 // !Not more than 255!

unsigned short won_games = 25;
unsigned short lost_games = 14;

struct AcceptedClient acceptedSockets[MAX_PLAYERS];
unsigned char acceptedSocketsCount = 0;

void acceptingConnections(int serverSocketFD);
DWORD WINAPI gameLoop(LPVOID lpParam);

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    int serverSocketFD = createTCPIPv4Socket();
    struct sockaddr_in *serverAddress = createIPv4Adress("", 2000);
    
    if (!bindAndListen(&serverSocketFD, &serverAddress)) return 1;

    acceptingConnections(serverSocketFD);

    closesocket(serverSocketFD);
    WSACleanup();
    return 0;
}

void acceptingConnections(int serverSocketFD) {
    while (1) {
        struct AcceptedClient* clientSocket = acceptIncomingConnection(serverSocketFD);
        if (clientSocket == NULL) continue;
        
        acceptedSockets[acceptedSocketsCount++] = *clientSocket;
        CreateThread(NULL, 0, gameLoop, clientSocket, 0, NULL);
    }
}

DWORD WINAPI gameLoop(LPVOID lpParam) {
    printf("Client connected.\n");

    struct AcceptedClient *pSocket = (struct AcceptedClient *)lpParam;
    //TODO: Select random word
    struct WordElement word[5] = {{'H', FALSE}, {'E', FALSE}, {'L', FALSE}, {'L', FALSE}, {'O', FALSE}};

    boolean isLost = FALSE;
    boolean isWon = FALSE;
    unsigned char remaining_hp = 3;
    
    char received_character;

    while (1) {
        if (!sendAndRecv(&pSocket, &isLost, &isWon, word, &remaining_hp, &received_character))
            return 0;

        checkIfCharacterIsInWord(word, received_character, &remaining_hp);
        checkIfWonOrLost(word, &isLost, &isWon, &remaining_hp);
    }
}