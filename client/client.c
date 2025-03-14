#include "../common/common.h"
#include "client_functions.h"

boolean isLost = FALSE;
boolean isWon = FALSE;
unsigned char currently_playing;
unsigned short won_games;
unsigned short lost_games;

int main() {

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    int serverSocketFD = createTCPIPv4Socket();
    struct sockaddr_in *address = createIPv4Adress("127.0.0.1", 2000);

    if (!connectAndCheck(serverSocketFD, address)) 
        return 1;
    
    char entered_character;
    
    while (1) {
        if (!recvAndCheck(serverSocketFD))
            break;

        displayStatsAndGetch(&entered_character);
        
        if (!sendChar(serverSocketFD, &entered_character))
            break;
    }

    closesocket(serverSocketFD);
    WSACleanup();
    return 0;
}