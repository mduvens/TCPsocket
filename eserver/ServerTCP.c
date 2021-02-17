#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include "helpers/DieWithError.h" /* for DieWithError() */
#include "helpers/HandleTCP.h" /* for HandleTCPClient() */

#define MAXPENDING 5    /* Maximum queue size */


int main(int argc, char *argv[])
{
    int serverSocket;                  
    int clientSocket;                   
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAdrress; 
    unsigned short serverPort;     
    unsigned int clientAddressLength;            

    if (argc != 2)     /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]);
        exit(1);
    }
    printf("%d", argc);
    serverPort = atoi(argv[1]);  /* First arg:  local port */

    /* Create the socket - socket(Communication Domain (IPv4,UNIX), Socket Type (STREAM/DGRAM), Protocol (TCP/UDP)) */
    if ((serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        DieWithError("Server socket() failed");
    }
      
    /* Construct local address structure */
    memset(&serverAddress, 0, sizeof(serverAddress));   /* Zero out structure */
    serverAddress.sin_family = AF_INET;                /* Internet address family */
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    serverAddress.sin_port = htons(serverPort);      /* Local port */

    /* Bind the socket to an adress - bind(Socket, Address, Size of Address) */
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
        DieWithError("Server bind failed");
    }

    /* "Activate" the socket - listen(Socket, Queue limit) */
    if (listen(serverSocket, MAXPENDING) < 0){
        DieWithError("Server listen() failed");
    }

    for (;;) /* Run until proccess is killed */
    {
        clientAddressLength = sizeof(clientAdrress);
        /* Accept the connection - accept(Server Socket, Client Address, Size of Client Address) */
        if ((clientSocket = accept(serverSocket, (struct sockaddr *) &clientAdrress, &clientAddressLength)) < 0){
            DieWithError("Server accept() failed");
        }
            
        printf("Handling client %s\n", inet_ntoa(clientAdrress.sin_addr));

        HandleTCPClient(clientSocket);
    }

}
