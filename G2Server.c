#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "miniRSA.h"
#define BUFF_SIZE 2048

int main(int argc, char const *argv[]) 
{ 
    int connectSock, dataSocket, sockRead; 
    struct sockaddr_in fullAddr; 
    int addrlen = sizeof(fullAddr); 
    char buffer[1024] = {0};
    char message[1000];

    long fileSize;
    char* fContent;

    fullAddr.sin_family = AF_INET; 
    fullAddr.sin_port = htons(atoi(argv[1])); 
    fullAddr.sin_addr.s_addr = INADDR_ANY; 

    memset(fullAddr.sin_zero, '\0', sizeof fullAddr.sin_zero);
       
    // Creating socket file descriptor 
    if ((connectSock = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    // Forcefully attaching socket to the port 8080 
    if (bind(connectSock, (struct sockaddr *)&fullAddr, sizeof(fullAddr))<0) 
    { 
        perror("Bind issue:"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(connectSock, 5) < 0) 
    { 
        perror("Listen issue:"); 
        exit(EXIT_FAILURE); 
    } 

    // while((dataSocket = accept(connectSock, (struct sockaddr *)&fullAddr, (socklen_t*)&addrlen))<0) {
    //     int pid;
    //     if((pid = fork()) == 0) {
    //         while (recv(dataSocket, message, 1000, 0)>0) {
    //             printf("Message Received: %s\n", message);
    //             //An extra breaking condition can be added here (to terminate the child process)            
    //             strcpy(message, "");
    //         }
    //         exit(0);
    //     }
    // }

    
        if ((dataSocket = accept(connectSock, (struct sockaddr *)&fullAddr, (socklen_t*)&addrlen))<0) 
        { 
            perror("Accept issue:"); 
            exit(EXIT_FAILURE); 
        }else{
            while (1){
                sockRead = read( dataSocket, buffer, BUFF_SIZE); 
                strcpy(message, strtok(buffer, "\n"));
        
                if(strcmp(message, ".bye") == 0){
                    printf("Received:\n%s\n Shutting Down...\n Have a good day!\n",message);
                    close(dataSocket);
                    exit(0);
                }

                printf("Received:\n%s\n",buffer );
                printf("Return Message? Type .bye to quit:\n");
                fgets(buffer, BUFF_SIZE, stdin);
                strcpy(message, strtok(buffer, "\n"));

                if(strcmp(message, ".bye") == 0){
                    printf("Shutting Down...\n Have a good day!\n");
                    send(dataSocket, message, strlen(message), 0);
                    close(dataSocket);
                    exit(0);
                }else{
                    send(dataSocket, message, strlen(message), 0);
                }

            }
    }
    
    close(dataSocket);
    return 0; 
} 