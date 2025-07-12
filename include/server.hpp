/*
 * server.hpp
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

#ifndef HTTP_INCLUDE_SERVER_H_
#define HTTP_INCLUDE_SERVER_H_

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>


namespace http
{
    class TCPServer {
        public:
            TCPServer(/* args */);
            ~TCPServer();
        private:
            int ServerSocket;
            sockaddr_in ServerAddress;
            socklen_t ServerLength;
            int CreateServerSocket();
            int CloseServerSocket();
            int ServerHandler();

    };
    
} // namespace http

#endif // HTTP_INCLUDE_SERVER_H_