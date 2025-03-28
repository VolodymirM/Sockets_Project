#ifndef SERVER_FUN_LIB
#define SERVER_FUN_LIB

#define MAX_PLAYERS 10 // !Not more than 255!
#define MAX_HP 3
#define MAX_WORDS 200
#define WORD_LENGTH 5

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
void initWord(struct WordElement word[]);
void wordToString(struct WordElement word[], char *wordString);
boolean sendAndRecv(struct AcceptedClient **pSocket, boolean *isLost, boolean *isWon, 
    struct WordElement word[], unsigned char *remaining_hp, char *received_character);
void checkIfCharacterIsInWord(struct WordElement word[], char received_character, unsigned char *remaining_hp);
void checkIfWonOrLost(struct WordElement word[], boolean *isLost, boolean *isWon, unsigned char *remaining_hp);

#endif // SERVER_FUN_LIB