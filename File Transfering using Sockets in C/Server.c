#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main() {

    int serverSocket = socket(AF_INET,SOCK_STREAM,0);
    // AF_INET represents IPv4 protocol
    // SOCK_STREAM represents TCP
    // 0 represents  Internet Protocol

    struct sockaddr_in serverAddres;
    serverAddres.sin_family = AF_INET;
    serverAddres.sin_port = htons(1881); // Port Number is 1881
    serverAddres.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(serverSocket,(struct sockaddr*) &serverAddres,sizeof(serverAddres));

    listen(serverSocket,1);

    int clientSocket = accept(serverSocket,NULL,NULL);

    FILE* filePointer;
    char temp[256];
    int line = 0;

    filePointer = fopen("textTosend.txt","r");

 // Firstly number of lines of the text file is being counted.
    while(1) {

        fgets(temp,256,filePointer);
        line++;
        if(feof(filePointer))
            break;

    }

    fclose(filePointer);
    sprintf(temp,"%d",line);
    send(clientSocket,temp,256,0);   // Secondly number of Line is being send to client.

    FILE* filePointer2;
    filePointer2 = fopen("textTosend.txt","r");
    char txBuffer[256];

    while(1) {   // Thirdly We send the lines of text file to client untill we reach end of file.

        fgets(txBuffer,256,filePointer);
        send(clientSocket,txBuffer,256,0);
        if(feof(filePointer2))
            break;
    }

    fclose(filePointer2);
    close(serverSocket);


}
