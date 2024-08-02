#include <stdexcept>
#include <string>

class SocketException : public std::runtime_error
{
private:
    /* data */
public:
    SocketException(const std::string& message) : runtime_error(message){

    }
};

class IOException : public SocketException
{
private:
    /* data */
public:
    IOException() : SocketException("IO Exception!"){

    }
};

class BadFileDescriptorException : public SocketException{
private: 
    /* data */

public: 
    BadFileDescriptorException() : SocketException("Invalid File Descriptor!"){

    }
};

class ConnectionAbortedException : public SocketException{
private:
    /* data */

public:
    ConnectionAbortedException() : SocketException("Connection Aborted!"){

    }
};

class ListenAccessException : public SocketException
{
private:
    /* data */
public:
    ListenAccessException(/* args */) : SocketException("Invalid Privileges!"){
        
    }
};

class ReadOverflowException : public SocketException
{
private:
    /* data */
public:
    ReadOverflowException(/* args */) : SocketException("Read Overflow Exception!"){

    }
};

class NoFileDescriptorsException : public SocketException{
private:
    /* data */
public:
    NoFileDescriptorsException() : SocketException("No File Descriptors Available for this Process!"){

    }
};

class WriteTooLargeException : public SocketException
{
private:
    /* data */
public:
    WriteTooLargeException(/* args */) : SocketException("Write Exceeds Max File Size Exception!"){

    }
};

class WritePipeClosedException : public SocketException
{
private:
    /* data */
public:
    WritePipeClosedException(/* args */) : SocketException("Pipe Closed Exception!"){

    }
};
