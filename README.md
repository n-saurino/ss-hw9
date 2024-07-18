# ss-hw9
Introduction to Networking

# Objectives

- Understand the fundamentals of networking, including sockets, TCP/IP, UDP, and asynchronous I/O.
- Gain hands-on experience in creating client-server applications using sockets.
- Learn to handle basic network communication and data exchange between processes.

# Reading

1. **“Unix Network Programming, Volume 1: The Sockets Networking API” by W. Richard Stevens**
    - Chapter 1: Introduction
    - Chapter 3: Sockets Introduction
    - Chapter 4: Elementary TCP Sockets
2. **“TCP/IP Sockets in C: Practical Guide for Programmers” by Michael J. Donahoo and Kenneth L. Calvert**
    - Chapter 1: Introduction to Sockets
    - Chapter 2: Basic TCP Sockets
    - Chapter 4: Basic UDP Sockets

# Tasks

1. **TCP Client-Server Application**
    - Write a simple TCP client-server application.
    - The server should listen on a specified port, accept connections from clients, and echo back any message it receives.
    - The client should connect to the server, send a message, and print the response from the server.
2. **UDP Client-Server Application**
    - Write a simple UDP client-server application.
    - The server should listen on a specified port and echo back any message it receives.
    - The client should send a message to the server and print the response.
3. **Asynchronous I/O with Sockets**
    - Implement an asynchronous TCP server using select or poll.
    - The server should handle multiple client connections concurrently without using multi-threading.
    - The server should echo back messages received from any client.
4. **Error Handling and Robustness**
    - Enhance your TCP and UDP applications to include proper error handling.
    - Ensure that your applications handle scenarios such as network errors, invalid input, and client disconnections gracefully.
5. **Documentation and Best Practices**
    - Write a README file that explains the following:
        - The basics of TCP/IP and UDP communication.
        - The differences between TCP and UDP and when to use each protocol.
        - Common pitfalls in network programming and how to avoid them.
    - Ensure your code follows best practices, such as proper indentation, meaningful variable names, and comments explaining the purpose of complex code sections.

# Submission

- Create a GitHub repository for your assignment.
- Commit your code, including the README file, to the repository.
- Ensure your repository is private and share access with your instructor.

# Evaluation Criteria

- **Correctness**: The programs should compile and run correctly, performing the specified tasks.
- **Networking Implementation**: Proper use of TCP and UDP sockets, and handling of asynchronous I/O.
- **Error Handling**: Robust error handling and graceful handling of network issues.
- **Code Quality**: Clean, readable, and well-documented code following best practices.
- **README File**: Clear and comprehensive explanation of networking concepts and challenges.

## **Task 1: TCP Client-Server Application**

### TCP Server

```cpp
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int valread = read(new_socket, buffer, 1024);
    std::cout << buffer << std::endl;
    send(new_socket, hello, strlen(hello), 0);
    std::cout << "Hello message sent" << std::endl;
    close(new_socket);
    close(server_fd);
    return 0;
}
```

### TCP Client

```cpp
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char* hello = "Hello from client";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\n Socket creation error \n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed \n";
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    std::cout << "Hello message sent" << std::endl;
    int valread = read(sock, buffer, 1024);
    std::cout << buffer << std::endl;
    close(sock);
    return 0;
}
```

## **Task 2: UDP Client-Server Application**

### UDP Server

```cpp
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;
    len = sizeof(cliaddr);
    n = recvfrom(sockfd, (char*)buffer, 1024, MSG_WAITALL, (struct sockaddr*)&cliaddr, (socklen_t*)&len);
    buffer[n] = '\0';
    std::cout << "Client : " << buffer << std::endl;
    sendto(sockfd, buffer, n, MSG_CONFIRM, (const struct sockaddr*)&cliaddr, len);
    std::cout << "Echo message sent." << std::endl;

    close(sockfd);
    return 0;
}
```

### UDP Client

```cpp
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    const char* hello = "Hello from client";
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;
    sendto(sockfd, (const char*)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr*)&servaddr, sizeof(servaddr));
    std::cout << "Hello message sent." << std::endl;

    n = recvfrom(sockfd, (char*)buffer, 1024, MSG_WAITALL, (struct sockaddr*)&servaddr, (socklen_t*)&len);
    buffer[n] = '\0';
    std::cout << "Server : " << buffer << std::endl;

    close(sockfd);
    return 0;
}
```