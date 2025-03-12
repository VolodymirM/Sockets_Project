#ifndef SERVER_FUN_LIB
#define SERVER_FUN_LIB

struct AcceptedClient * acceptIncomingConnection(int serverSocketFD);
DWORD WINAPI exchangeDataWithClient(LPVOID lpParam);

#endif // SERVER_FUN_LIB