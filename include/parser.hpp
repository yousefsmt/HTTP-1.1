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
 * Date: 02-Jul-2024
 */

#pragma once

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

    static const std::unordered_map<std::string, HTTPmethods> MethodMAP = {
        { "OPTIONS", HTTPmethods::OPTIONS },
        { "GET",     HTTPmethods::GET },
        { "HEAD",    HTTPmethods::HEAD },
        { "POST",    HTTPmethods::POST },
        { "PUT",     HTTPmethods::PUT },
        { "DELETE",  HTTPmethods::DELETE },
        { "TRACE",   HTTPmethods::TRACE },
        { "CONNECT", HTTPmethods::CONNECT }
    };

    class ParserMessage {
        public:
            ParserMessage();
            ~ParserMessage();

            json parserHTTPrequest(std::string&);

            bool parserHTTPrequest_Line(std::string&, json*);
            bool parserHTTPrequest_Header(std::string&, json*);
            bool parserHTTPrequest_Body(std::string&, json*);

            HTTPmethods StringToHTTPMethod(const std::string&);           

            std::string CreateHTTP_Response();


        private:
            HTTPmethods method;
            json HTTPmessage_request;
            json HTTPmessage_response;
            
    };

} // namespace http
