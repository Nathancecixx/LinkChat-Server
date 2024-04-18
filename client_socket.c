#include <string.h>
#include "client_socket.h"

//C
CLIENT_SOCKET CreateClientSocket(int Number){
	CLIENT_SOCKET socket;

	socket.number = Number;

	return socket;
}
CLIENT_SOCKET CopyClientSocket(CLIENT_SOCKET Socket){
	CLIENT_SOCKET socket;

	socket.number = Socket.number;

	return socket;
}

//R
int GetClientSocketNum(CLIENT_SOCKET Socket){
	return Socket.number;
}

bool CompareClientSocket(CLIENT_SOCKET Socket1, CLIENT_SOCKET socket2){
	return Socket1.number - socket2.number;
}

//U

//D
void DestroyClientSocket(CLIENT_SOCKET* Socket){

}