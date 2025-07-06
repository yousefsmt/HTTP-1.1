#include <iostream>
#include <nlohmann/json.hpp>
#include <sys/time.h>

#include "parser.hpp"

using json = nlohmann::json;

int main(){
    http::ParserMessage ParserTools;
    json ParsedMessage;

    std::string TestCase {"PUT /submit-form HTTP/1.1\n"
                "Host: www.example.com\n"
                "User-Agent: curl/7.68.0\n"
                "Accept: */*\n"
                "Content-Type: application/x-www-form-urlencoded\n"
                "Content-Length: 27\n"
                "\n"
                "name=John+Doe&age=25\n"};

    
    ParsedMessage = ParserTools.parserHTTPrequest(TestCase);

    return 0;
}