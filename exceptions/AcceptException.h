#include <exception>
#include <stdexcept>
#include <string>

class AcceptException : public std::runtime_error{
public:
    AcceptException(const std::string& message) : runtime_error(message){
        // pass in an error string
    }

private:

};

class AcceptInvalidFileDescriptor : public AcceptException{
public:
    AcceptInvalidFileDescriptor() : AcceptException("Invalid File Descriptor!"){
        
    }

private:

};

class AcceptConnectionAborted : public AcceptException{
public:
    AcceptConnectionAborted() : AcceptException("Connection Aborted!"){

    }
private:

};