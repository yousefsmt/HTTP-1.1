#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

#include "parser.hpp"

// /*
// POST /submit-form HTTP/1.1
// Host: www.example.com
// User-Agent: curl/7.68.0
// Accept: */*
// Content-Type: application/x-www-form-urlencoded
// Content-Length: 27

// name=John+Doe&age=25
// */

using json = nlohmann::json;

http::ParserMessage::ParserMessage(){}
http::ParserMessage::~ParserMessage(){}

json http::ParserMessage::parseHTTPrequest(std::string& MessageRequest){
    json ParsedMsg_Request {};

    ParsedMsg_Request.push_back("Request-Line");
    ParsedMsg_Request.push_back("general-header");
    ParsedMsg_Request.push_back("request-header");
    ParsedMsg_Request.push_back("message-body");



    return ParsedMsg_Request;
}

json http::ParserMessage::parseHTTPresponse(std::string& MessageResponse){}