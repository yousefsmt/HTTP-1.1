/*
 * parser.hpp
 *
 * This header defines the structures and functions used to parse HTTP/1.1
 * messages, including both requests and responses. It provides core
 * functionality for interpreting and extracting components of HTTP communication,
 * such as headers, status lines, and message bodies, making it suitable for use
 * in both server-side and client-side applications.
 *
 * Key Features:
 * - Parses HTTP/1.1 request lines (method, URI, HTTP version)
 * - Parses HTTP/1.1 response status lines (HTTP version, status code, reason phrase)
 * - Extracts and stores HTTP headers in key-value format
 * - Handles message body parsing with content-length support
 * - Designed for modular integration into custom HTTP applications
 *
 * Usage:
 * Include this header to enable HTTP message parsing in your project.
 * This parser is lightweight and intended for manual or low-level HTTP implementations.
 *
 * Author: Yousef.smt  
 * Date: 02-Jul-2024
*/

#ifndef HTTP_INCLUDE_PARSER_H_
#define HTTP_INCLUDE_PARSER_H_

#include <iostream>
#include <nlohmann/json.hpp>

namespace http
{
    using json = nlohmann::json;

    enum class HTTPmethods{
        OPTIONS,
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
        TRACE,
        CONNECT,
        UNKNOWN
    };

    class ParserMessage {
        public:
            ParserMessage() = default;
            ~ParserMessage() = default;

            json parserHTTPrequest(std::string&);
        private:
            HTTPmethods ExtractedMETHOD;
            json ParsedHTTP_request;

            const bool parserHTTPrequest_Line(const std::vector<std::string>&, json&);
            const bool parserHTTPrequest_Header(const std::vector<std::string>&, json&);
            const bool parserHTTPrequest_Body(const std::vector<std::string>&, json&) const; 
    };

} // namespace http

#endif // HTTP_INCLUDE_PARSER_H_