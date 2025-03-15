#ifndef SERVER_FUN_LIB
#define SERVER_FUN_LIB

struct AcceptedClient 
{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    boolean isAccepted;
};

extern unsigned char acceptedSocketsCount;
extern unsigned short won_games;
extern unsigned short lost_games;

struct WordElement
{
    char character;
    boolean isGuessed;
};

boolean bindAndListen(int *serverSocketFD, struct sockaddr_in **serverAddress);
struct AcceptedClient * acceptIncomingConnection(int serverSocketFD);
void wordToString(struct WordElement word[], char *wordString);
boolean sendAndRecv(struct AcceptedClient **pSocket, boolean *isLost, boolean *isWon, 
    struct WordElement word[], unsigned char *remaining_hp, char *received_character);

#endif // SERVER_FUN_LIB