#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include "networkhandler.h"


int main(void){


    int server_socket = InitServer();

	AcceptConnection(server_socket);




    /*
	//Create server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//defines the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bind the socket to our specified ip and port
	bind(server_socket, 
	(struct sockaddr*) &server_address, 
	sizeof(server_address));


	//UPDATE

	listen(server_socket, 5);

	int client_socket;
	PLISTNODE client_List_Head = NULL;

	while((client_socket = accept(server_socket, (struct sockaddr *) NULL, NULL))){
		printf("\nClient (%d) Connected!\n", client_socket);

		//Create a new process
		int process_id;
		if((process_id = fork()) == 0){

			//Add new connection to list
			Insert_Tail(&client_List_Head, client_socket);

			int bytes_Recieved;
			char client_response [80];
			while((bytes_Recieved = recv(client_socket, client_response, 80, 0)) > 0){
				printf("bytes_Recieved;: %d\n", bytes_Recieved);
                printf("Process Id # %d\n", process_id);
				printf("Message %d: %s\n", client_socket, client_response);
				//Broadcast method
				//Print_List_Size(client_List_Head);
				broadcast_message(client_List_Head, client_socket, client_response);
			}
			printf("Client (%d) Disconnected\n", client_socket);
			Delete_Value(&client_List_Head, client_socket);
			close(client_socket);
            exit(0);
		}
	}

 */
	CloseConnection();
    close(server_socket);

    return 0;

}
