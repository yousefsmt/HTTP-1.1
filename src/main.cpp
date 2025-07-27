#include <iostream>
#include <nlohmann/json.hpp>

#include "parser.hpp"
#include "server.hpp"

using json = nlohmann::json;
using namespace http;

int main(int argc, char* argv[]) {
    char ip[16] = "0.0.0.0";
    char port[6] = "80";

    ParserMessage ParserObj;
    json ParsedMessage;

    switch (argc) {
        case 1:
            break;
        case 2:
            strncpy(ip, argv[1], sizeof(ip) - 1);
            ip[sizeof(ip) - 1] = '\0';
            break;
        case 3:
            strncpy(ip, argv[1], sizeof(ip) - 1);
            ip[sizeof(ip) - 1] = '\0';
            strncpy(port, argv[2], sizeof(port) - 1);
            port[sizeof(port) - 1] = '\0';
            break;
        default:
            std::cerr << "Usage: " << argv[0] << " [IP_ADDRESS] [PORT]\n";
            return 1;
    }

    try {
        TCPServer runServer(ip, port); 
    } catch (const std::exception& ex) {
        std::cerr << "Failed to start server: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
