#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include "../unp.h"

int AsyncTCPServer(){

    int i, max_i, max_fd, listen_fd, conn_fd, sock_fd, n_ready;
    int client[FD_SETSIZE];

    ssize_t n;
    fd_set r_set, all_set;
    char buffer[MAXLINE];
    socklen_t cli_len;
    struct sockaddr_in cli_address, server_address;

    // create listening socket/file descriptor
    listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&server_address, sizeof(server_address));

    // define server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERV_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind
    Bind(listen_fd, (struct sockaddr*)&server_address, sizeof(server_address));
    
    // listen
    Listen(listen_fd, LISTENQ);

    max_fd = listen_fd;
    max_i = -1;
    for(i = 0; i < FD_SETSIZE; ++i){
        client[i] = -1;
    }
    
    FD_ZERO(&all_set);
    FD_SET(listen_fd, &all_set);

    while(true){
        r_set = all_set;
        n_ready = Select(max_fd + 1, &r_set, NULL, NULL, NULL);

        if(FD_ISSET(listen_fd, &r_set)){
            cli_len = sizeof(cli_address);
            conn_fd = Accept(listen_fd, (struct sockaddr*)&cli_address, &cli_len);

            for(i = 0; i < FD_SETSIZE; ++i){
                if(client[i] < 0){
                    client[i] = conn_fd;
                    break;
                }
            }

            if(i == FD_SETSIZE){
                throw std::logic_error("too many clients");
            }

            // set this file descriptor bit in the fd array
            FD_SET(conn_fd, &all_set);

            if(conn_fd > max_fd){
                max_fd = conn_fd;
            }

            if(i > max_i){
                max_i = i;
            }

            // no more file descriptors ready to connect to
            if(--n_ready == 0){
                continue;
            }   
        }

        for(i = 0; i <= max_i; ++i){
            if((sock_fd = client[i]) < 0){
                continue;
            }

            if(FD_ISSET(sock_fd, &r_set)){
                if((n = Read(sock_fd, buffer, MAXLINE)) == 0){
                    // connection closed by client
                    // so close our file descriptor to that client
                    Close(sock_fd);
                    // reset the bit in the fd array to 0
                    FD_CLR(sock_fd, &all_set);
                    // remove the client's fd from the client array
                    client[i] = -1;
                }else{
                    Write(sock_fd, buffer, n);
                }

                // no more readable descriptors
                if(--n_ready <= 0){
                    break;
                }
            }
        }

    }

    return 0;
}