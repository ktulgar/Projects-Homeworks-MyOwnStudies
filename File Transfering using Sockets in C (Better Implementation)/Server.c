#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main() {

    int serverSocket = socket(AF_INET,SOCK_STREAM,0);
    // AF_INET represents IPv4 protocol
    // SOCK_STREAM represents TCP
    // 0 represents  Internet Protocol

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1881); // Port Number is 1881
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
    listen(serverSocket,1);

    int clientSocket = accept(serverSocket,NULL,NULL);

    FILE* filePointer = fopen("textTosend.txt","r"); // Open the file

    fseek(filePointer,0,SEEK_END);
    long size = ftell(filePointer);  // Find the size of text file
    char textFile[size]; // It will hold the text file.

    fseek(filePointer,0,SEEK_SET);
    fread(textFile,sizeof(textFile),1,filePointer); // Put the text file into char array


    send(clientSocket,&size,sizeof(size),0);  // Send information of the size to client
    send(clientSocket,textFile,sizeof(textFile),0); // Send char array to client

    fclose(filePointer);
    close(serverSocket);



}


