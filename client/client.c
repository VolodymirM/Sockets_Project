#include <conio.h>

#include "../common/common.h"
#include "client_functions.h"

int main() {

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    int serverSocketFD = createTCPIPv4Socket();
    struct sockaddr_in *address = createIPv4Adress("127.0.0.1", 2000);

    int result = connect(serverSocketFD, (struct sockaddr *)address, sizeof(*address));
    if (result == 0) {
        printf("Connected successfully!\n");
        system("pause");
    }
    else {
        printf("Failed to connect. Error Code: %d\n", WSAGetLastError());
        system("pause");
        return 1;
    }
    
    // Data received from the server
    boolean isLost = FALSE;
    boolean isWon = FALSE;
    unsigned char currently_playing;
    unsigned short won_games;
    unsigned short lost_games;
    // Data to be sent to the server
    char entered_character;

    while (1) {
        system("cls");

        int recvResult1 = recv(serverSocketFD, (char *)&isLost, sizeof(isLost), 0);
        int recvResult2 = recv(serverSocketFD, (char *)&isWon, sizeof(isWon), 0);
        int recvResult3 = recv(serverSocketFD, (char *)&currently_playing, sizeof(currently_playing), 0);
        int recvResult4 = recv(serverSocketFD, (char *)&won_games, sizeof(won_games), 0);
        int recvResult5 = recv(serverSocketFD, (char *)&lost_games, sizeof(lost_games), 0);
    
        if (recvResult1 <= 0 || recvResult2 <= 0 || recvResult3 <= 0 || recvResult4 <= 0 || recvResult5 <= 0) {
            printf("Server disconnected.\n");
            system("pause");
            break;
        }

        if (isLost) {
            printf("You lost!\n");
            system("pause");
            break;
        }

        if (isWon) {
            printf("You won! Congratulations:)\n");
            system("pause");
            break;
        }
    
        printf("Playing now: %d\n", currently_playing);
        printf("Won games: %d\n", won_games);
        printf("Lost games: %d\n", lost_games);
    
        printf("Enter a character: ");
        entered_character = getch();
        
        if (send(serverSocketFD, &entered_character, 1, 0) == SOCKET_ERROR) {
            system("cls");
            printf("Failed to send data. Server may have disconnected.\n");
            system("pause");
            break;
        }
    }

    closesocket(serverSocketFD);
    WSACleanup();
    return 0;
}