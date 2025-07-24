#include <iostream>
#include <nlohmann/json.hpp>
#include <sys/time.h>
#include <cpr/cpr.h>

#include "parser.hpp"
#include "server.hpp"

using json = nlohmann::json;
using namespace http;

int main(int argc, char* argv[]) {
    std::string ip {"0.0.0.0"};
    std::string port {"80"};

    ParserMessage ParserTools;
    json ParsedMessage;

    switch (argc) {
        case 1:
            break;
        case 2:
            ip = argv[1];
            break;
        case 3:
            ip = argv[1];
            port = argv[2];
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
