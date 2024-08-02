#include <stdexcept>
#include <string>

class CloseException : public std::runtime_error{
private:
    /* data */

public:
    CloseException(const std::string& message) : runtime_error(message){

    }
};

class CloseBadFileDescriptor : public CloseException{
private:

public:
    CloseBadFileDescriptor() : CloseException("Invalid File Descriptor!"){

    }
};

class CloseIOException : public CloseException{
private:

public:
    CloseIOException() : CloseException("IO Exception!"){
        
    }
};
