#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
/*
- Write a simple TCP client-server application.
- The server should listen on a specified port, accept connections from clients, and echo back 
  any message it receives.
- The client should connect to the server, send a message, and print the response from the server.
*/


void Ex1(){
    // create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // define the socket address info
    // using the sockaddr_in struct
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the server socket
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    // set the socket to listen
    listen(server_socket, 5);

    // receive client connection and return the client socket value
    int client_socket = accept(server_socket, nullptr, nullptr);

    // set up buffer to parse client message
    char buffer[1024] = {0};
    recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Message from client: " << buffer << std::endl; 
    
    // close the server socket
    close(server_socket);




    
}
