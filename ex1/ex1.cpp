#pragma once
#include <thread>
#include "Client.cpp"
#include "Server.cpp"
#include "ScopedThread.cpp"

/*
- Write a simple TCP client-server application.
- The server should listen on a specified port, accept connections from clients, and echo back 
  any message it receives.
- The client should connect to the server, send a message, and print the response from the server.
*/

int Ex1(){
    std::thread t_server(TCP_Server);
    ScopedThread scoped_server(std::move(t_server));
    // Ensure server starts first
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread t_client(TCP_Client);
    ScopedThread scoped_client(std::move(t_client));

    return 0;
}
