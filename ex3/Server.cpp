#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>


int AsyncTCPServer(){
    // create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // define server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    
    // listen
    listen(server_socket, 5);
    
    // accept
    int client_socket = accept(server_socket, nullptr, nullptr);
    std::cout << "Client connection established" << std::endl;

    // recv
    char buffer[1024];
    recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Message from client at server: " << buffer << std::endl;

    int bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
    if(bytes_sent < 0){
        std::cout << "Message send failure!" << std::endl;
    }

    close(server_socket);

    return 0;
}