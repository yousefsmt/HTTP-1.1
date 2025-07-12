#include <iostream>
#include <nlohmann/json.hpp>
#include <sys/time.h>
#include <cpr/cpr.h>

#include "parser.hpp"
#include "server.hpp"

using json = nlohmann::json;
using namespace http;

int main(){
    ParserMessage ParserTools;
    TCPServer runServer("0.0.0.0", "8080");
    json ParsedMessage;

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

    ParsedMessage = ParserTools.parserHTTPrequest(TestCase1);

    return 0;
}