#include <stdio.h>    
#include <sys/socket.h> 
#include <unistd.h>     
#include <string.h>
#include "DieWithError.h"

#define RCVBUFSIZE 32   

void upperString(char * lower){  
    int i = 0;
    while(lower[i]){
        if(lower[i] >= 'a' && lower[i] <= 'z'){ /* Check if it's a lower case character  */
            lower[i] = lower[i] - 32;           /* If positive, convert it to upper case*/   
        }                    
        i++;            
    }  
}

void HandleTCPClient(int clientSocket)
{
    char echoBuffer[RCVBUFSIZE];   /* Buffer to store each communication*/
    int messageLength;  

    /* Get the client message - recv(Client Socket, Message Buffer, Size of Buffer)*/
    if ((messageLength = recv(clientSocket, echoBuffer, RCVBUFSIZE, 0)) < 0){
        DieWithError("Server didn't receive.");
    }
    
    while (messageLength > 0)      /* zero indicates end of transmission */
    {
        upperString(echoBuffer); /* Convert buffer to uppercase */

        /* Echo communication - send(Socket, Message, Size of Messagge, Special Options)*/
        if (send(clientSocket, echoBuffer, messageLength, 0) != messageLength){
            DieWithError("Server didn't send.");
        }

        /* Check for more data*/
        if ((messageLength = recv(clientSocket, echoBuffer, RCVBUFSIZE, 0)) < 0){
            DieWithError("Server didn't receive.");
        }

    }
    close(clientSocket);  /* Close client socket */
}
