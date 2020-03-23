#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 31337
#define IP "127.0.0.1"

int main(){

    //socket creation
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    //check for error in socket
    if(client_fd == -1){
        printf("%s", "socket error");
        exit(1);
    }

    //define the address structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr( IP );
    server_address.sin_port = htons( PORT );
    socklen_t addrlen = sizeof(server_address);

    //connect
    if(connect(client_fd, (const struct sockaddr *)&server_address, addrlen) == -1){
        printf("%s", "connection error");
        exit(1);
    }

    //send and recv
    while (1)
    {
        char buf[1024] = {0};
        char rbuf[1024] = {0};
        printf("%s", "message: ");
        fgets(buf, 1024, stdin);
        send(client_fd, &buf, sizeof(buf), 0);
        recv(client_fd, &rbuf, sizeof(rbuf), 0);
        printf("the server sent back : %s", rbuf);
    }

    close(client_fd);

    return 0;
}