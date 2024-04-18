#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


bool Insert_Head(PLISTNODE* Head, int SocketNum){
	PLISTNODE NewNode = (PLISTNODE) malloc (sizeof(LISTNODE));
	if(NewNode == NULL)
		return false;

	NewNode->socket = CreateClientSocket(SocketNum);

	if(*Head == NULL){
		*Head = NewNode;
		NewNode->next = NULL;
		return true;
	}

	NewNode->next = *Head;
	*Head = NewNode;
	return true;

}

bool Insert_Tail(PLISTNODE* Head, int SocketNum){

	PLISTNODE NewNode = (PLISTNODE) malloc(sizeof(LISTNODE));
	if(NewNode == NULL)
		return false;
    NewNode->socket = CreateClientSocket(SocketNum);
	

	if(*Head == NULL){
		*Head = NewNode;
		NewNode->next = NULL;
		return true;
	}


	PLISTNODE current = *Head;
	
	while(current->next != NULL){
		current = current->next;
	}
	
	current->next = NewNode;
	NewNode->next = NULL;

	return true;
}

bool Delete_Value(PLISTNODE* Head, int SocketNum) {

    //Checks if head is NULL
    if(*Head == NULL) return false;

	//Checks if head is desired value
	if(CompareClientSocket((*Head)->socket, CreateClientSocket(SocketNum)) == 0) {
		PLISTNODE tmp = *Head;
		*Head = (*Head)->next;
		free(tmp);
		return true;
	}


    //Iterates through list trying to find value
	PLISTNODE current = *Head;
	PLISTNODE prev = NULL;

	while (current != NULL){
        if(CompareClientSocket(current->socket, CreateClientSocket(SocketNum)) == 0) {
			prev->next = current->next;
			free(current);
			return true;
		}
		prev = current;
		current = current->next;
	}

	return false;
}

bool Print_List(PLISTNODE Head){
	PLISTNODE current = Head;
	
	while(current != NULL){
		printf("Socket # -> %d \n", GetClientSocketNum(current->socket));
		current = current->next;
	}

	printf("\n\n\n");
	return true;
}

void Print_List_Size(PLISTNODE Head){
	PLISTNODE current = Head;
	int count = 0;

	while(current != NULL){
		count++;
		current = current->next;
	}
	printf("Size Of List: %d\n", count);
}

bool Destroy_List(PLISTNODE* Head){
	PLISTNODE current = *Head;

	PLISTNODE prev = NULL;
	while(current != NULL){
		prev = current;
		current = current->next;
		free(prev);
	}

	*Head = NULL;
	return true;
}

bool Reverse_List(PLISTNODE* Current){
	return false;	
}
