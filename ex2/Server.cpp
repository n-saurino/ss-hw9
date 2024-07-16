#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

int UDP_Server(){
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // need to bind socket
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // then need to set socket to listen
    listen(server_socket, 5);
    std::cout << "Server listening" << std::endl;
    // need to accept
    int client_socket = accept(server_socket, nullptr, nullptr);

    // need to parse information from client
    char buffer[1024] = {0};
    sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);


    while(true){
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_address, &client_address_len);
        if (bytes_received < 0) {
            std::cerr << "Failed to receive message from client" << std::endl;
            continue;
        }

        std::cout << "Message from client at server: " << buffer << std::endl;

        // echo back to client
        ssize_t bytes_sent = sendto(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_address, client_address_len);
        if (bytes_sent < 0) {
            std::cerr << "Failed to send message to client" << std::endl;
        }
        break;
    }
    
    close(server_socket);
    return 0;
}