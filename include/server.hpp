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

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>

#include "parser.hpp"

#define BUFFER_SIZE 4096
#define BLOCK_SIZE 1000

namespace http {
class TCPServer : public ParserMessage {
public:
  TCPServer(const char *IPaddress, const char *Port);
  ~TCPServer();

  char Receive_Buffer[BUFFER_SIZE];

private:
  int ServerSocket, ClientSocket;
  sockaddr_in ServerAddress;
  socklen_t ServerLength;
  const char *IPaddress_;
  const char *Port_;
  bool CreateServerSocket();
  bool CloseServerSocket();
  bool AcceptHandler();
  bool ReceiveHandler();
  bool RunAllThread();
};

} // namespace http

#endif // HTTP_INCLUDE_SERVER_H_