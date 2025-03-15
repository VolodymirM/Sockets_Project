#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <malloc.h>

int createTCPIPv4Socket() {return socket(AF_INET, SOCK_STREAM, 0);}

struct sockaddr_in* createIPv4Adress(char *ip, int port) {
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    
    if (!address) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    address->sin_family = AF_INET;
    address->sin_port = htons(port);

    if (strlen(ip) == 0) address->sin_addr.s_addr = INADDR_ANY;
    else address->sin_addr.s_addr = inet_addr(ip);

    return address;
}