/*
 * parser.hpp
 *
 * This header file defines the structures and functions necessary to parse
 * HTTP/1.1 requests and responses. It provides functionality to interpret 
 * HTTP headers, methods, status lines, and message bodies, enabling seamless
 * integration into HTTP servers or clients.
 *
 * Features:
 * - Parses HTTP/1.1 request lines (method, URI, version)
 * - Parses HTTP/1.1 response status lines (version, status code, reason phrase)
 * - Extracts and stores HTTP headers and message body
 *
 * Usage:
 * Include this file in your project to add HTTP message parsing capabilities.
 *
 * Author: Yousef.smt
 * Date: [Optional Date]
 */


#pragma once

/*

POST /users HTTP/1.1
Host: example.com
Content-Type: application/x-www-form-urlencoded
Content-Length: 49

name=FirstName+LastName&email=bsmth%40example.com

Request       = Request-Line
                *(( general-header
                    | request-header
                    | entity-header ) CRLF)
                CRLF
                [ message-body ]

Request-Line   = Method SP Request-URI SP HTTP-Version CRLF
*/
#include <iostream>
#include <nlohmann/json.hpp>

namespace http {

    using json = nlohmann::json;

    enum class HTTPmethods {
        OPTIONS,
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
        TRACE,
        CONNECT
    };

    class ParserMessage {
        public:
            ParserMessage();
            ~ParserMessage();

            json parseHTTPrequest(std::string& MessageRequest);
            json parseHTTPresponse(std::string& MessageResponse);


        private:
            HTTPmethods method;
            json HTTPmessage_request;
            json HTTPmessage_response;
            
    };

} // namespace http
