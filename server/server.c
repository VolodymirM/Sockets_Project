#include "../common/common.h"
#include "server_functions.h"

int main() {
    
    unsigned char players;
    unsigned short won_games;
    unsigned short lost_games;
    init_stats(&players, &won_games, &lost_games);

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

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    int clientSocketFD = accept(serverSocketFD, (struct sockaddr*)&clientAddress, &clientAddressSize);

    // char buffer[BUFFER_SIZE];
    // recv(clientSocketFD, buffer, BUFFER_SIZE, 0);
    // printf("%s\n", buffer);
    //while (1) {
        //if (getchar() == 'q') break;

        send(clientSocketFD, (const char *)&players, sizeof(players), 0);
        send(clientSocketFD, (const char *)&won_games, sizeof(won_games), 0);
        send(clientSocketFD, (const char *)&lost_games, sizeof(lost_games), 0);        

        char received_character;
        recv(clientSocketFD, &received_character, sizeof(received_character), 0);
        printf("Received character: %c\n", received_character);
    //}

    closesocket(clientSocketFD);
    closesocket(serverSocketFD);
    WSACleanup();
    return 0;
}