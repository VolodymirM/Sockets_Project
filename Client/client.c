#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>

#include "client_functions.h"

int main() {

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD == -1) {
        printf("Error creating socket\n");
        return 1;
    }

    char *ip = "142.251.10.113";
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    
    server.sin_addr.s_addr = inet_addr(ip);

    int result = connect(socketFD, (struct sockaddr *)&server, sizeof(server));
    if (result == 0)
        printf("Connected succesfully\n");
    else
        printf("Failed to connect. Error Code: %d\n", WSAGetLastError());

    closesocket(socketFD);
    WSACleanup();
    return 0;
}