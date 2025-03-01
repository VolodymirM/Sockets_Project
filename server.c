#include "common.h"
#include "server_functions.h"

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

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    
    int clientSocketFD = accept(serverSocketFD, (struct sockaddr*)&clientAddress, &clientAddressSize);

    char buffer[BUFFER_SIZE];
    recv(clientSocketFD, buffer, BUFFER_SIZE, 0);
    printf("%s\n", buffer);

    char *message = "Message from server";
    send(clientSocketFD, message, strlen(message), 0);

    closesocket(clientSocketFD);
    closesocket(serverSocketFD);
    WSACleanup();
    return 0;
}