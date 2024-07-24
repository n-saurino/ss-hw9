#include <exception>
#include <iostream>
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

#define MAXLINE 1024
#define SERV_PORT 8080
#define LISTENQ 5

// Accept
int Accept(int socket, struct sockaddr* address,
       socklen_t* address_len){
    try
    {
        return accept(socket, address, address_len);
    }catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw std::logic_error("Accept Error");
    }
}

// Bind
int Bind(int socket, const struct sockaddr* address,
       socklen_t address_len){
        try
        {
            return bind(socket, address, address_len);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw std::logic_error("Bind Error");
        }   
}

// Close
int Close(int fildes){
    try
    {
        return close(fildes);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw std::logic_error("Close Error");
    }
}

// Listen
int Listen(int socket, int backlog){
    try
    {
        return listen(socket, backlog);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw std::logic_error("Listen Error");
    }
}

// Read
ssize_t Read(int fildes, void* buf, size_t nbyte){
    try
    {
        return read(fildes, buf, nbyte);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw std::logic_error("Read Error");
    }
}

// Select
int Select(int nfds, fd_set* readfds, fd_set* writefds,
    fd_set* errorfds, struct timeval* timeout){
    try
    {
        return select(nfds, readfds, writefds, errorfds, timeout);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw std::logic_error("Select Error");
    }
    
    }

// Socket
int Socket(int domain, int type, int protocol){
    try
    {
        return socket(domain, type, protocol);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw std::logic_error("Socket Error");
    }
    
}

// Write
ssize_t Write(int __fd, const void* __buf, size_t __nbyte){
    try
    {
        return write(__fd, __buf, __nbyte);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw std::logic_error("Write Error");
    }
    
}
