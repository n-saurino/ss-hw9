#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

int Server(){
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in socket_address;
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(8080);
    socket_address.sin_addr.s_addr = INADDR_ANY;

    // need to bind socket
    bind(server_socket, (sockaddr*)&socket_address, sizeof(socket_address));

    // then need to set socket to listen
    listen(server_socket, 5);

    // need to accept
    int client_socket = accept(server_socket, nullptr, nullptr);

    // need to parse information from client
    char buffer[1024] = {0};

    // recv
    recv(client_socket, buffer, sizeof(buffer), 0);

    std::cout << "Message from client: " << buffer << std::endl;

    return 0;
}