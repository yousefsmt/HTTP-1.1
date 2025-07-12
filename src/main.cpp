#include <iostream>
#include <nlohmann/json.hpp>
#include <sys/time.h>
#include <cpr/cpr.h>

#include "parser.hpp"
#include "server.hpp"

using json = nlohmann::json;
using namespace http;

int main(){
    timeval start {}, stop {};
    ParserMessage ParserTools;
    TCPServer runServer;
    json ParsedMessage;
    long double x {};

    std::string TestCase1 {"PUT /submit-form HTTP/1.1\n"
                "Host: www.example.com\n"
                "User-Agent: curl/7.68.0\n"
                "Accept: */*\n"
                "Content-Type: application/x-www-form-urlencoded\n"
                "Content-Length: 27\n"
                "\n"
                "name=John+Doe&age=25\n"};

    std::string TestCase2 =
                "POST /api/data HTTP/1.1\r\n"
                "Host: example.com\r\n"
                "User-Agent: CustomClient/1.0\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: 18\r\n"
                "\r\n"
                "{\"key\":\"value\"}";


    gettimeofday(&start, NULL);
    ParsedMessage = ParserTools.parserHTTPrequest(TestCase1);
    gettimeofday(&stop, NULL);

    x = (stop.tv_sec - start.tv_sec)*1000.0 + (stop.tv_usec - start.tv_usec);

    std::cout << "Elapsed Time: " << x << '\n';

    std::cout << std::setw(4) << ParsedMessage << '\n';

    return 0;
}