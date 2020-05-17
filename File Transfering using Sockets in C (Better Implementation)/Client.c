#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "arpa/inet.h"

int main() {

    int clientSocket = socket(AF_INET,SOCK_STREAM,0);
    // AF_INET represents IPv4 protocol
    // SOCK_STREAM represents TCP
    // 0 represents  Internet Protocol

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1881);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //LocalHost

    connect(clientSocket,(struct sockaddr*)&serverAddress, sizeof(serverAddress));

    long size;
    recv(clientSocket,&size,sizeof(size),0); // Receive the size of text file

    char textFile[size];   // It will hold received text file.

    recv(clientSocket,textFile, sizeof(textFile),0);  // Receive the text file as char array

    FILE* filePointer = fopen("textToreceive.txt","w"); // Create an empty text file
    fwrite(textFile,sizeof(textFile),1,filePointer);

    fclose(filePointer);
    close(clientSocket);



}