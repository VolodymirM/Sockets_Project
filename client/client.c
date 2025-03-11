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
        return 1;
    }
    
    char entered_character;
    unsigned char players;
    unsigned short won_games;
    unsigned short lost_games;

    while (1) {
        system("cls");
        
        recv(serverSocketFD, (char *)&players, sizeof(players), 0);
        recv(serverSocketFD, (char *)&won_games, sizeof(won_games), 0);
        recv(serverSocketFD, (char *)&lost_games, sizeof(lost_games), 0);
        
        printf("Players: %d\n", players);
        printf("Won games: %d\n", won_games);
        printf("Lost games: %d\n", lost_games);

        printf("Enter a character: ");
        entered_character = getch();
        
        send(serverSocketFD, &entered_character, 1, 0);
    }

    // char buffer[BUFFER_SIZE];
    // recv(serverSocketFD, buffer, BUFFER_SIZE, 0);
    // printf("%s\n", buffer);

    closesocket(serverSocketFD);
    WSACleanup();
    return 0;
}