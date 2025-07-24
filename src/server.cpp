#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "server.hpp"

namespace http
{
    TCPServer::TCPServer(const std::string& IPaddress, const std::string& Port)
        : ServerSocket(0), ClientSocket(0), ServerAddress({0}), ServerLength(0), IPaddress_(IPaddress), Port_(Port)
    {
        CreateServerSocket();
    }
    
    TCPServer::~TCPServer(){
        if(!CloseServerSocket())
            std::cout << "ERROR: Sockets close failed.\n";
    }

    const bool TCPServer::CreateServerSocket(){
        uint8_t isCorrect {};
        uint16_t PortNumber_Casted {};

        ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (ServerSocket == -1){
            perror("Creation socket: ");
            return false;
        }

        PortNumber_Casted = static_cast<uint16_t>(std::stoi(Port_));

        ServerAddress.sin_family = AF_INET;
        inet_pton(AF_INET, IPaddress_.c_str(), &(ServerAddress.sin_addr.s_addr));
        ServerAddress.sin_port = htons(PortNumber_Casted);
        ServerLength = sizeof(ServerAddress);

        isCorrect = bind(ServerSocket, (sockaddr *)&ServerAddress, ServerLength);
        if (isCorrect == -1){
            perror("Bind failed: ");
            return false;
        }

        isCorrect = listen(ServerSocket, 20);
        if (isCorrect == -1){
            perror("Listen failed: ");
            return false;
        }
        else{
            std::cout << "Server listening...\n";
        }

        sockaddr_in clidd {};
        socklen_t cliddddlen {};
        cliddddlen = sizeof(clidd);
        int cli = accept(ServerSocket, (sockaddr*)&clidd, &cliddddlen);

        return true;
    }

    const bool TCPServer::CloseServerSocket(){
        uint8_t isClose {};

        isClose = close(ServerSocket);
        if (isClose == -1){
            perror("Close failed:");
            return false;
        }
        isClose = close(ClientSocket);
        if (isClose == -1){
            perror("Close failed:");
            return false;
        }

        return true;
    }
    
} // namespace http