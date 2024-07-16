#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

int UDP_Client(){
    // create client socket
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // define socket address 
    sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(8080);
    client_address.sin_addr.s_addr = INADDR_ANY;

    // connect socket to server
    connect(client_socket, (struct sockaddr*)&client_address, sizeof(client_address));
    const char* message = "Hello from Client";
    std::cout << "Sending message" << std::endl;
    sendto(client_socket, message, strlen(message), 0, (struct sockaddr*)&client_address, sizeof(client_address));
    std::cout << "Message sent" << std::endl;

    /*
    // receive message from server
    char buffer[1024] = {0};
    sockaddr_in server_address;
    socklen_t server_address_len = sizeof(server_address);
    recvfrom(client_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_address, &server_address_len);


    std::cout << "Message from server at client: " << buffer << std::endl;
    */
    close(client_socket);
    return 0;
}