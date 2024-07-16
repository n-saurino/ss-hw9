#pragma once
#include <thread>
#include "Client.cpp"
#include "Server.cpp"
#include "../ex1/ScopedThread.cpp"

/*
- Write a simple UDP client-server application.
- The server should listen on a specified port and echo back any message it receives.
- The client should send a message to the server and print the response.
*/

int Ex2(){
    std::thread t_server(UDP_Server);
    ScopedThread scoped_server(std::move(t_server));
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread t_client(UDP_Client);
    ScopedThread scoped_client(std::move(t_client));

    return 0;
}