#pragma once
#include "../ex1/ex1.cpp"
#include "Server.cpp"

/*
- Implement an asynchronous TCP server using select or poll.
- The server should handle multiple client connections concurrently without using multi-threading.
- The server should echo back messages received from any client.
*/

int Ex3(){
    
    std::thread server(AsyncTCPServer);
    ScopedThread scoped_server(std::move(server));

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread client1(TCP_Client);
    ScopedThread scoped_client(std::move(client1));

    std::thread client2(TCP_Client);
    ScopedThread scoped_client2(std::move(client2));

    std::thread client3(TCP_Client);
    ScopedThread scoped_client3(std::move(client3));

    return 0;
}