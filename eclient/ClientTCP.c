#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <stdlib.h>     
#include <string.h>    
#include <unistd.h>     
#include "helpers/DieWithError.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */
#define MAXSIZE 256 /* Max size of message */


int main(int argc, char *argv[])
{
    int clientSocket;  
    char *serverIP;                  
    struct sockaddr_in serverAddress; 
    unsigned short serverPort;     
    char echoString[MAXSIZE];             
    char echoBuffer[RCVBUFSIZE];   
    unsigned int echoStringLen;      
    int bytesReceived; /* can be -1 with error, so it's not unsigned */
    int totalBytes; 

    if(argc != 3)    /* Test for correct number of arguments */
    {
       fprintf(stderr, "!Error! \nUsage: %s <Server IP> <Echo Port>\n",argv[0]);
       exit(1);
    }

    serverIP = argv[1];
    serverPort = atoi(argv[2]); 

    /* Create the socket - socket(Communication Domain (IPv4,UNIX), Socket Type (STREAM/DGRAM), Protocol (TCP/UDP)) */
    if ((clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        DieWithError("Client socket() failed");
    }

    /* Define the echoServer's address */
    memset(&serverAddress, 0, sizeof(serverAddress));       /* Zero out structure */
    serverAddress.sin_family = AF_INET;                     /* Internet address family */
    serverAddress.sin_addr.s_addr = inet_addr(serverIP);    /* Server IP address */
    serverAddress.sin_port = htons(serverPort); /* Server port */

    /* Connect to server - connect(Socket, Server Address, Size of Server Address)*/
    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
        DieWithError("Client couldn't connect");
    }

    /* Get the message from user */
    printf("Enter a message: ");
    fgets(echoString, sizeof(echoString), stdin);  
    echoStringLen = strlen(echoString);   

    /* Send communication - send(Socket, Message, Size of Messagge, Special Options)*/
    if (send(clientSocket, echoString, echoStringLen, 0) != echoStringLen){
        DieWithError("Client message has different size than expected");
    }

    /* Receive back the sent/echoed string */
    totalBytes = 0;
    printf("Echo: ");                
    while (totalBytes < echoStringLen)
    {
        /* Receive echo - recv(Socket, Message, Size of Message, Special Options) */
        if ((bytesReceived = recv(clientSocket, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0){
            DieWithError("recv() failed or connection closed prematurely");
        }
        totalBytes += bytesReceived;  
        echoBuffer[bytesReceived] = '\0'; /* Close/End the string */  
        printf("%s", echoBuffer);     
    }
    printf("Closed connection with %s \n", inet_ntoa(serverAddress.sin_addr));    
    close(clientSocket);
    exit(0);
}
