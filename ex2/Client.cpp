#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

int UDP_Client(){
    // create client socket
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // define socket address 
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // send message to server
    const char* message = "Hello from Client";
    std::cout << "Client sending message" << std::endl;
    int send_result = sendto(client_socket, message, strlen(message), 0, (struct sockaddr*)&server_address, sizeof(server_address));
    if(send_result < 0){
        std::cerr << "Client failed to send message" << std::endl;
        close(client_socket);
        return 1;
    }
    std::cout << "Client message sent" << std::endl;

    
    // receive message from server
    char buffer[1024] = {0};
    socklen_t server_address_len = sizeof(server_address);
    ssize_t bytes_received = recvfrom(client_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_address, &server_address_len);
    if(bytes_received > 0){
        std::cout << "Message from server at client: " << buffer << std::endl; 
    }else{
        std::cout << "Server Message not received at client" << std::endl;
    }
    
    close(client_socket);
    return 0;
}