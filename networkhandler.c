#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

#include "networkhandler.h"
#include "stack.h"


#define MAX_ROOMS   5

pthread_mutex_t list_mutex;
int server_socket;
PLISTNODE client_list_heads[MAX_ROOMS] = {0};


int InitServer(){
    //Create server socket
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

    return server_socket;

}

int AcceptConnection(int Server_Socket){
    listen(server_socket,5);

    int client_socket;
    pthread_mutex_init(&list_mutex, NULL);

    while((client_socket = accept(server_socket, NULL, NULL))){
        printf("Client (%d) Connected\n", client_socket);

        pthread_t thread_id;
        int* new_sock = (int*) malloc (sizeof(int));
        *new_sock = client_socket;

        if(pthread_create(&thread_id, NULL, HandleConnection, (void*) new_sock) < 0){
            fprintf(stderr, "Could not create thread\n");
            free(new_sock);
        }
    }
/*
    for(int i = 0; i < MAX_ROOMS; i++){
        Destroy_List(&client_list_heads[i]);
    }
*/
    close(server_socket);
    pthread_mutex_destroy(&list_mutex);

    return 0;
}

void* HandleConnection(void* Client_Socket){
   int sock = *(int*)Client_Socket;

    int roomNum = 0;


    pthread_mutex_lock(&list_mutex);
    Insert_Tail(&client_list_heads[roomNum], sock);
    pthread_mutex_unlock(&list_mutex);



    char client_response[80];
    int bytes_recieved;
    while((bytes_recieved = recv(sock, client_response, 80, 0) > 0)){
        //check if response was a command
        if(client_response[0] == '$'){

            //Delete client out of current room
            pthread_mutex_lock(&list_mutex);
            Delete_Value(&client_list_heads[roomNum], sock);
            pthread_mutex_unlock(&list_mutex);

            //Take new room command
            printf("Command Recieved...\n");
            roomNum = (int) client_response[1] - 48;
            printf("\n\n\n");

            //Add client to new room
            pthread_mutex_lock(&list_mutex);
            Insert_Tail(&client_list_heads[roomNum], sock);
            pthread_mutex_unlock(&list_mutex);


            //Remove this
            for(int i = 0; i < MAX_ROOMS; i ++){
                Print_List_Size(client_list_heads[i]);
            }


            continue;
        }
        printf("bytes_Recieved;: %d\n", bytes_recieved);
        printf("Message %d: %s\n", sock, client_response);
        printf("Room #: %d\n", roomNum);
        broadcast_message( sock, roomNum, client_response);
        printf("\n\n\n");
    }

    pthread_mutex_lock(&list_mutex);
    Delete_Value(&client_list_heads[roomNum], sock);
    pthread_mutex_unlock(&list_mutex);

    printf("Socket (%d) Disconected.\n", sock);
    close(sock);
    return NULL;
}

bool broadcast_message(int Src_Socket, int Room_Number, char* message){
    PLISTNODE current = client_list_heads[Room_Number];
    CLIENT_SOCKET src_socket = CreateClientSocket(Src_Socket);

    while(current != NULL){
        printf("Current Socket = %d\n", current->socket.number);
        if(CompareClientSocket(current->socket, src_socket) != 0) {
            printf("Compared: %d - %d \n", current->socket.number, src_socket.number);
            send(current->socket.number, message, strlen(message), 0);
        }
        current = current->next;
    }

    return true;
}

bool CloseConnection(){

    for(int i = 0; i < MAX_ROOMS; i++){
        Destroy_List(&client_list_heads[i]);
    }

    close(server_socket);

    return true;
}