#include<stdbool.h>


int InitServer(void);

int AcceptConnection(int Server_Socket);

void* HandleConnection(void* Client_Socket);

bool broadcast_message(int Src_Socket, int Room_Number, char* message);

bool CloseConnection(void);

