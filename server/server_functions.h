#ifndef SERVER_FUN_LIB
#define SERVER_FUN_LIB

extern unsigned char acceptedSocketsCount;
extern unsigned short won_games;
extern unsigned short lost_games;

boolean bindAndListen(int *serverSocketFD, struct sockaddr_in **serverAddress);
struct AcceptedClient * acceptIncomingConnection(int serverSocketFD);
boolean sendAndRecv(struct AcceptedClient **pSocket, boolean *isLost, boolean *isWon, char *received_character);

#endif // SERVER_FUN_LIB