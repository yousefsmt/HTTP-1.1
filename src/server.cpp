#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "server.hpp"

namespace http
{
    TCPServer::TCPServer(const std::string IPaddress, const std::string Port){
        CreateServerSocket(IPaddress, Port);
    }

    TCPServer::~TCPServer(){
        if(CloseServerSocket())
            std::cout << "ERROR: Sockets close failed.\n";
    }

    int TCPServer::CreateServerSocket(const std::string IPaddress, const std::string Port){
        int isCorrect {};

        ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (ServerSocket == -1){
            perror("Creation socket: ");
            return 0;
        }

        ServerAddress.sin_family = AF_INET;
        ServerAddress.sin_addr.s_addr = INADDR_ANY;
        ServerAddress.sin_port = htons(8080);
        ServerLength = sizeof(ServerAddress);

        isCorrect = bind(ServerSocket, (sockaddr *)&ServerAddress, ServerLength);
        if (isCorrect == -1){
            perror("Bind failed: ");
            return 0;
        }

        isCorrect = listen(ServerSocket, 20);
        if (isCorrect == -1){
            perror("Listen failed: ");
            return 0;
        }

        ServerHandler();
        return 1;
    }

    int TCPServer::CloseServerSocket(){
        int isClose {};

        isClose = close(ServerSocket);
        if (isClose == -1){
            perror("Close failed:");
            return 0;
        }
        isClose = close(ClientSocket);
        if (isClose == -1){
            perror("Close failed:");
            return 0;
        }

        return 1;
    }

    void* TCPServer::AcceptHandler(void* args){
        auto* server = static_cast<TCPServer*>(args);
        sockaddr_in ClientAddress {};
        socklen_t ClientLength {};
        int isRecv {};
        ClientLength = sizeof(ClientAddress);
        while (true)
        {
            server->ClientSocket = accept(server->ServerSocket, (sockaddr*)&ClientAddress, &ClientLength);
            if (server->ClientSocket == -1){
                perror("Accept failed:");
                return 0;
            }
            isRecv = read(server->ClientSocket, server->Buffer, 1023);
            std::cout << server->Buffer;
        }
        return nullptr;
    }

    int TCPServer::ServerHandler(){
        pthread_create(&AcceptThread, NULL, &TCPServer::AcceptHandler, this);
        pthread_detach(AcceptThread);

        return 1;
    }
    
} // namespace http