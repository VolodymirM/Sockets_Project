#ifndef CLIENT_FUN_LIB
#define CLIENT_FUN_LIB

extern boolean isLost;
extern boolean isWon;
extern unsigned char currently_playing;
extern unsigned short won_games;
extern unsigned short lost_games;

boolean connectAndCheck(int serverSocketFD, struct sockaddr_in *address);
boolean recvAndCheck(int serverSocketFD);
void displayStatsAndGetch(char *entered_character);
boolean sendChar(int serverSocketFD, char *entered_character);

#endif // CLIENT_FUN_LIB