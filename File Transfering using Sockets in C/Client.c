#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "stdlib.h"
#include "arpa/inet.h"

int main() {

    int clientSocket = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_port = htons(1881);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // LocalHost


    connect(clientSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress));

    // Firstly we get number of lines that text file contains.We are gonna use that information.
    char line[256];
    recv(clientSocket,line,256,0);
    int lines = atoi(line); // Change it to integer.
    char rxBuffer[256];

    FILE* filePointer;
    filePointer = fopen("textToreceive.txt","w");
    int x = 0;

     while(lines>0) {

        recv(clientSocket,rxBuffer,256,0);
        fputs(rxBuffer,filePointer);
        lines--;

     }

     fclose(filePointer);
     close(clientSocket);

}

