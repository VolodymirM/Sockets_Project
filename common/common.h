#ifndef COMMON_LIB
#define COMMON_LIB

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <malloc.h>

int createTCPIPv4Socket();
struct sockaddr_in* createIPv4Adress(char *ip, int port);

#endif // COMMON_LIB