/*
 * server.h
 *
 * This header file defines the structures and functions required to implement
 * a basic HTTP/1.1 server. It provides the core components for accepting client
 * connections, processing requests, and sending appropriate HTTP responses.
 *
 * Key Features:
 * - Listens for and accepts incoming HTTP client connections
 * - Handles request routing and response generation
 * - Supports sending standard HTTP/1.1 status lines, headers, and bodies
 * - Designed for integration into custom or embedded HTTP server applications
 *
 * Usage:
 * Include this file to add HTTP server functionality to your application.
 * This module focuses on server-side behavior; it does not perform HTTP
 * parsing.
 *
 * Author: Yousef.smt
 * Date: 02-Jul-2024
 */

#ifndef HTTP_INCLUDE_SERVER_H_
#define HTTP_INCLUDE_SERVER_H_

#include "parser.hpp"

#include <array>
#include <iostream>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <thread>

namespace http
{

constexpr size_t block_size{1000};
constexpr size_t buffer_size{4096};
constexpr size_t MAX_EVENTS{16};

class TCPServer : public ParserMessage
{
  public:
    TCPServer(const std::string& ip_address, const std::string& port_address);

    TCPServer(const TCPServer&)            = delete;
    TCPServer& operator=(const TCPServer&) = delete;
    TCPServer(TCPServer&&)                 = delete;
    TCPServer& operator=(TCPServer&&)      = delete;

    ~TCPServer();

  private:
    std::array<char, buffer_size> receive_buffer{};
    int                           server_socket{};
    int                           client_socket{};
    int                           epoll_fd{};
    sockaddr_in                   server_address{};
    socklen_t                     server_length{};
    epoll_event                   event{};
    epoll_event                   polled_events[MAX_EVENTS];
    std::string                   ip_address_;
    std::string                   port_;
    bool                          CreateServerSocket();
    bool                          CloseServerSocket() const;
    bool                          AcceptHandler();
    bool                          RunAllThread();
    ///////////////// Example /////////////////////////////
    const char* http_response = "HTTP/1.1 200 OK\r\n"
                                "Date: Thu, 28 Aug 2025 14:35:00 GMT\r\n"
                                "Server: CustomServer/1.0\r\n"
                                "Content-Type: application/json; charset=utf-8\r\n"
                                "Content-Length: 49\r\n"
                                "Connection: keep-alive\r\n"
                                "\r\n"
                                "{\n"
                                "  \"message\": \"Hello, you reached the root!\"\n"
                                "}\r\n";
    ////////////////////////////////////////////////////////
};

} // namespace http

#endif // HTTP_INCLUDE_SERVER_H_