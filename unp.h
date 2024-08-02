#pragma once
#include <exception>
#include <iostream>
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include "exceptions/BindException.h"
#include "exceptions/AcceptException.h"
#include "exceptions/CloseException.h"
#include "exceptions/SocketException.h"

#define MAXLINE 1024
#define SERV_PORT 8080
#define LISTENQ 5

void CheckSocketError(int result){
    if(result < 0){
        switch(errno){
            case EBADF:
                throw BadFileDescriptorException();
                break;

            case ECONNABORTED:
                throw ConnectionAbortedException();
                break;
            
            case EIO:
                throw IOException();
                break;

            case EACCES:
                throw ListenAccessException();
                break;

            case EOVERFLOW:
                throw ReadOverflowException();
                break;

            case EMFILE:
                throw NoFileDescriptorsException();
                break;

            case EFBIG:
                throw WriteTooLargeException();
                break;

            case EPIPE:
                throw WritePipeClosedException();
                break;

            default:
                throw SocketException(strerror(errno));
                break;
        }
    }
}

// Accept
int Accept(int socket, struct sockaddr* address,
       socklen_t* address_len){
    int result = accept(socket, address, address_len);
    CheckSocketError(result);
    return result;
}

// Bind
int Bind(int socket, const struct sockaddr* address,
       socklen_t address_len){
        int result = bind(socket, address, address_len);
        CheckSocketError(result);
        return result;
}

// Close
int Close(int fildes){
   int result = close(fildes);
    CheckSocketError(result);
    return result;
    
}

// Listen
int Listen(int socket, int backlog){
    int result = listen(socket, backlog);
    CheckSocketError(result);
    return result;
}

// Read
ssize_t Read(int fildes, void* buf, size_t nbyte){
    int result = read(fildes, buf, nbyte);
    CheckSocketError(result);
    return result;
}

// Select
int Select(int nfds, fd_set* readfds, fd_set* writefds,
    fd_set* errorfds, struct timeval* timeout){
    int result = select(nfds, readfds, writefds, errorfds, timeout);
    CheckSocketError(result);
    return result;
}

// Socket
int Socket(int domain, int type, int protocol){
    int result = socket(domain, type, protocol);
    CheckSocketError(result);
    return result;    
}

// Write
ssize_t Write(int __fd, const void* __buf, size_t __nbyte){
    int result = write(__fd, __buf, __nbyte);
    CheckSocketError(result);
    return result;
}
