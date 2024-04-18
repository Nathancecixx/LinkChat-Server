#include <stdbool.h>

#define MAX_NAME 	20
#define MAX_PASSWORD    25

typedef struct client_socket{
	int number;
    //char username [MAX_NAME];
    //char password [MAX_PASSWORD];
}CLIENT_SOCKET;


//C
CLIENT_SOCKET CreateClientSocket(int Number);
CLIENT_SOCKET CopyClientSocket(CLIENT_SOCKET Socket);

//R
int GetClientSocketNum(CLIENT_SOCKET Socket);
bool CompareClientSocket(CLIENT_SOCKET Socket1, CLIENT_SOCKET socket2);

//U

//D
void DestroyClientSocket(CLIENT_SOCKET* Socket);