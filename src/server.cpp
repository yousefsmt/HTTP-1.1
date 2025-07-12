#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "server.hpp"

namespace http
{
    TCPServer::TCPServer(){
        CreateServerSocket();
    }

    TCPServer::~TCPServer(){
        CloseServerSocket();
    }

    int TCPServer::CreateServerSocket(){
        int isBind {}, isListen {}, isAccept {};

        sockaddr_in cli {};
        socklen_t cli_add {};

        ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (ServerSocket == -1){
            perror("server socket: ");
            return 0;
        }

        ServerAddress.sin_family = AF_INET;
        ServerAddress.sin_addr.s_addr = INADDR_ANY;
        ServerAddress.sin_port = htons(8080);
        ServerLength = sizeof(ServerAddress);

        isBind = bind(ServerSocket, (sockaddr *)&ServerAddress, ServerLength);
        if (isBind == -1){
            perror("bind failed: ");
            return 0;
        }

        isListen = listen(ServerSocket, 20);
        if (isListen == -1){
            perror("Listen failed: ");
            return 0;
        }

        isAccept = accept(ServerSocket, (sockaddr*)&cli, &cli_add);
        if (isAccept == -1){
            perror("Listen failed: ");
            return 0;
        }

        return 1;
    }

    int TCPServer::CloseServerSocket(){

        return 1;

    }
    int TCPServer::ServerHandler(){

        return 1;

    }
    
} // namespace http