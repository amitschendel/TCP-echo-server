#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 31337

int main(){

    int server_fd, client_fd;
    //create the socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    //check for creation error
    if(server_fd == -1){
        printf("%s", "socket error\n");
        exit(1);
    }

    //define the address structure
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    //bind the address to the socket
    socklen_t address_length = sizeof(address);
    if(bind(server_fd, (const struct sockaddr *)&address, address_length) == -1){
        printf("%s", "bind error\n");
        exit(1);
    }

    //create listener with backlog of 1
    if(listen(server_fd, 1) == -1){
        printf("%s", "listen error\n");
        exit(1);
    }

    //accept connection
    struct sockaddr_in client_address;
    socklen_t addrlen;
    client_fd = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t*)&addrlen);
    if(client_fd == -1){
        printf("%s", "connection accepting error\n");
        exit(1);
    }

    while (1)
    {
        //recv message
        char buf[1024] = {0};
        int read = recv(client_fd, &buf, sizeof(buf), 0);
        if(!read) break;//done reading
        printf("the client sent: %s", buf);
        //send message
        send(client_fd, &buf, sizeof(buf), 0);
    }
    
    close(client_fd);
    close(server_fd);

    return 0;
}