#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>

boolean isLost;
boolean isWon;
unsigned char currently_playing;
unsigned short won_games;
unsigned short lost_games;
unsigned char remaining_hp;
char word[6];

boolean connectAndCheck(int serverSocketFD, struct sockaddr_in *address) {
    int result = connect(serverSocketFD, (struct sockaddr *)address, sizeof(*address));
    
    if (result != 0){
        printf("Failed to connect. Error Code: %d\n", WSAGetLastError());
        system("pause");
        return FALSE;
    }
    
    printf("Connected successfully!\n");
    system("pause");
    system("cls");
    return TRUE;
}

boolean recvAndCheck(int serverSocketFD) {
    int recvResult1 = recv(serverSocketFD, (char *)&isLost, sizeof(isLost), 0);
    int recvResult2 = recv(serverSocketFD, (char *)&isWon, sizeof(isWon), 0);
    int recvResult3 = recv(serverSocketFD, (char *)&currently_playing, sizeof(currently_playing), 0);
    int recvResult4 = recv(serverSocketFD, (char *)&won_games, sizeof(won_games), 0);
    int recvResult5 = recv(serverSocketFD, (char *)&lost_games, sizeof(lost_games), 0);
    int recvResult6 = recv(serverSocketFD, (char *)&word, 6 * sizeof(char), 0);
    int recvResult7 = recv(serverSocketFD, (char *)&remaining_hp, sizeof(remaining_hp), 0);

    if (recvResult1 <= 0 || recvResult2 <= 0 || recvResult3 <= 0 || recvResult4 <= 0 
        || recvResult5 <= 0 || recvResult6 <= 0 || recvResult7 <= 0) {
        printf("Server disconnected.\n");
        system("pause");
        return FALSE;
    }

    if (isLost) {
        printf("You lost!\n");
        system("pause");
        return FALSE;
    }

    if (isWon) {
        printf("You won! Congratulations:)\n");
        system("pause");
        return FALSE;
    }

    return TRUE;
}

void displayStatsAndGetch(char *entered_character) {
    printf("Playing now: %d\n", currently_playing);
    printf("Won games: %d\n", won_games);
    printf("Lost games: %d\n", lost_games);
    
    printf("\n%s\n", word);
    printf("\nAttempts left: %d\n", remaining_hp);

    printf("\nEnter a character: ");
    *entered_character = getch();
}

boolean sendChar(int serverSocketFD, char *entered_character) {
    if (send(serverSocketFD, entered_character, 1, 0) == SOCKET_ERROR) {
        system("cls");
        printf("Failed to send data. Server may have disconnected.\n");
        system("pause");
        return FALSE;
    }

    system("cls");
    return TRUE;
}