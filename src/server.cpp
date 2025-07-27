#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <nlohmann/json.hpp>

#include "server.hpp"

namespace http
{
    using json = nlohmann::json;

    TCPServer::TCPServer(const char* IPaddress, const char* Port)
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
        inet_pton(AF_INET, IPaddress_, &(ServerAddress.sin_addr.s_addr));
        ServerAddress.sin_port = htons(PortNumber_Casted);
        ServerLength = sizeof(ServerAddress);

        isCorrect = bind(ServerSocket, (sockaddr *)&ServerAddress, ServerLength);
        if (isCorrect == -1){
            perror("Bind failed: ");
            return false;
        }

        isCorrect = listen(ServerSocket, BLOCK_SIZE);
        if (isCorrect == -1){
            perror("Listen failed: ");
            return false;
        }
        else{
            std::cout << "Server listening...\n";
        }

        RunAllThread();    
        return true;
    }

    const bool TCPServer::CloseServerSocket(){
        uint8_t isClose {};

        isClose = close(ServerSocket);
        if (isClose == -1){
            perror("Close server:");
            return false;
        }
        isClose = close(ClientSocket);
        if (isClose == -1){
            perror("Close client:");
            return false;
        }

        return true;
    }
    
    const bool TCPServer::AcceptHandler(){
        sockaddr_in ClientAddress {};
        socklen_t ClientLength {};
        ClientLength = sizeof(ClientAddress);

        while (true){    
            ClientSocket = accept(ServerSocket, (sockaddr*)&ClientAddress, &ClientLength);
            if (ClientSocket == -1){
                perror("accept failed: ");
                break;
            }
            else
                ReceiveHandler();    
        }

        return true;
    }

    const bool TCPServer::ReceiveHandler(){
        int isCorrect {};
        std::memset(Receive_Buffer, 0, BUFFER_SIZE);

        isCorrect = recv(ClientSocket, Receive_Buffer, BUFFER_SIZE-1, 0);
        if (Receive_Buffer[0] != '\0'){
            json j;
            ParserMessage parse;
            std::string x = Receive_Buffer;
            std::cout << x;
            std::cout << "************************";
            j = parse.parserHTTPrequest(x);
            std::cout << std::setw(4) << j << '\n';
        }
            
        return true;
    }

    const bool TCPServer::RunAllThread(){
        std::thread AcceptThread(&TCPServer::AcceptHandler, this);   
        AcceptThread.join();
        return true;
    }

} // namespace http