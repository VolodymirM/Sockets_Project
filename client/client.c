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
    if (result == 0) 
        printf("Connected successfully!\n");
    else {
        printf("Failed to connect. Error Code: %d\n", WSAGetLastError()); 
        return 1;
    }

    char *message = "Message from client";
    send(serverSocketFD, message, strlen(message), 0);

    char buffer[BUFFER_SIZE];
    recv(serverSocketFD, buffer, BUFFER_SIZE, 0);

    printf("%s\n", buffer);

    closesocket(serverSocketFD);
    WSACleanup();
    return 0;
}