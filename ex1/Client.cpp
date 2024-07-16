#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 

void Client(){
    // creating client IPv4 TCP socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // defining server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // connect to server
    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    const char* client_message = "Hello from client!";
    send(client_socket, client_message, strlen(client_message), 0);
    
    // close
    close(client_socket);

}
