#pragma once
#include <exception>
#include <iostream>
#include <netinet/in.h> 
#include <stdexcept>
#include <string>
#include <sys/socket.h> 
#include <unistd.h>

class BindException : public std::runtime_error{
public:
    BindException(const std::string& message) : runtime_error(message){

    }
};

class BindIOException : public BindException{
public:
    BindIOException() : BindException("IO Exception!"){

    }
};

class BindInvalidFileDescriptor : public BindException{
public:
    BindInvalidFileDescriptor(): BindException("Invalid File Descriptor!"){

    }
};