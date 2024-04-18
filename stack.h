#include <stdbool.h>
#include "client_socket.h"

typedef struct listnode{
	CLIENT_SOCKET socket;
	void* next;
}LISTNODE, *PLISTNODE;


bool Insert_Head(PLISTNODE* Head, int SocketNum);

bool Insert_Tail(PLISTNODE* Head, int SocketNum);

bool Delete_Value(PLISTNODE* Head, int SocketNum);

bool Print_List(PLISTNODE Head);
void Print_List_Size(PLISTNODE Head);

bool Destroy_List(PLISTNODE* Head);

bool Reverse_List(PLISTNODE* Head);
