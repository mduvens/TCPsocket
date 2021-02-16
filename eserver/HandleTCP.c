#include <stdio.h>    
#include <sys/socket.h> 
#include <unistd.h>     
#include <string.h>
#define RCVBUFSIZE 32   

void DieWithError(char *errorMessage); 
void upperString(char *lower);

void upperString(char * lower){  /* Convert to upper case */ 
    int i = 0;
    while(lower[i]){
        if(lower[i] >= 'a' && lower[i] <= 'z')    /* Check if it's a lower case character  */
            lower[i] = lower[i] - 32;             /* If positive, convert it to upper case*/   
        i++;            
    }  
}

void HandleTCPClient(int clientSocket)
{
    char echoBuffer[RCVBUFSIZE];   
    int messageLength;                  
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

        /* Check for more data - recv(Client Socket, Message Buffer, Size of Buffer)*/
        if ((messageLength = recv(clientSocket, echoBuffer, RCVBUFSIZE, 0)) < 0){
            DieWithError("Server didn't receive.");
        }

    }
    close(clientSocket);    /* Close client socket */
}
