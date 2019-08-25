#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "miniRSA.h"
#define BUFFER_SIZE 10000 
#define HOST_SIZE 1000
#define PAGE_SIZE 1000
#define PORT_SIZE 5
//#define HEADER_SIZE 1000
#define MESSAGE_SIZE 1000

int main(int argc, char* argv[])
{
    struct addrinfo hints;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo* result;

    int socketfd;
    int byte_count;

    char buffer[BUFFER_SIZE];
    char host[HOST_SIZE];
    char port[PORT_SIZE];
    char page[PAGE_SIZE];
    char message[MESSAGE_SIZE];
    char code[MESSAGE_SIZE*5];

    long E;
    long C;
    long D;
    long DC;

    //char header[HEADER_SIZE];

    if (argc < 7){
        printf("Too Little Arguments, supply arguments as host, and in this order");
        exit(0);
    }
    else
    {
        strcpy(host, argv[1]);
        strcpy(port, argv[2]);
        E = atoi(argv[3]);
        C = atoi(argv[4]);
        D = atoi(argv[5]);
        DC = atoi(argv[6]);
    }

    // printf("Host: ");
    // fgets(host, HOST_SIZE, stdin);
    // strtok(host, "\n");

    // printf("Page: ");
    // fgets(page, PAGE_SIZE, stdin);
    // strtok(page, "\n");
    
    // printf("Port: ");
    // fgets(port, PORT_SIZE, stdin);
    // strtok(port, "\n");

    // strcpy(header, "GET ");
    // strcat(header, page);
    // strcat(header, " HTTP/1.1\nHost: ");
    // strcat(header, host);
    // strcat(header, "\r\n\r\n");

    memset(&hints, 0, sizeof(hints));
    getaddrinfo(host, port, &hints, &result);
    socketfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol); //Make socket

    printf("Connecting\n");

    if(connect(socketfd, result->ai_addr, result->ai_addrlen) == 0) //Connect to socket
    {
        printf("Connection Successful\n");
        while(1){
            printf("What's your Message? Type .bye to quit:\n");
            fgets(buffer, BUFFER_SIZE, stdin);

            strcpy(message, strtok(buffer, "\n"));

            if(strcmp(message, ".bye") == 0){
                printf("Client shutting down... Have a good day!\n");
                send(socketfd, message, strlen(message), 0);
                exit(0);
            }
            else
            {
                sprintf(code, "%ld", encrypt(message[0], E, C));
                // for(int i = 1; i < strlen(message); i++){
                //     strcat(code, " ");
                //     strcat(code, encrypt(message[i], E, C);
                // }
                printf("%s", code);
                send(socketfd, code, strlen(message), 0);
            }   
    
            byte_count = recv(socketfd, buffer, sizeof(buffer) - 1, 0); //Read data to buffer 
            buffer[byte_count] = 0; //Add null terminator

            printf("Received:\n%s\n",buffer); //Print buffer
            strcpy(message, strtok(buffer, "\n"));
            if(strcmp(message, ".bye") == 0){
                printf("Client shutting down... Have a good day!\n");
                exit(0);
            }
        }
        
    }
    else
    {
        printf("Connection Failed\n");
    }   

    return 0;
}