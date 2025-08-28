#include "server.hpp"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sys/socket.h>
#include <unistd.h>

namespace http
{
using json = nlohmann::json;

TCPServer::TCPServer(const std::string& ip_address, const std::string& port_address)
    : ip_address_(ip_address), port_(port_address)
{
    CreateServerSocket();
}

TCPServer::~TCPServer()
{
    if (!CloseServerSocket())
    {
        std::cout << "ERROR: Sockets close failed.\n";
    }
}

bool TCPServer::CreateServerSocket()
{
    int      is_correct{};
    uint16_t port_number_cast{};

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Creation socket: ");
        return false;
    }

    port_number_cast = static_cast<uint16_t>(std::stoi(port_));

    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip_address_.c_str(), &(server_address.sin_addr.s_addr));
    server_address.sin_port = htons(port_number_cast);
    server_length           = sizeof(server_address);

    is_correct = bind(server_socket, reinterpret_cast<sockaddr*>(&server_address), server_length);
    if (is_correct == -1)
    {
        perror("Bind failed: ");
        return false;
    }

    is_correct = listen(server_socket, block_size);
    if (is_correct == -1)
    {
        perror("Listen failed: ");
        return false;
    }
    else
    {
        epoll_fd = epoll_create1(EPOLL_CLOEXEC);

        event.events  = EPOLLIN;
        event.data.fd = server_socket;

        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &event);

        if (epoll_fd == -1)
        {
            perror("epoll_create: ");
        }
        std::cout << "Server listening...\n";
        RunAllThread();
        return true;
    }

    return true;
}

bool TCPServer::CloseServerSocket() const
{
    int is_close{};

    is_close = close(server_socket);
    if (is_close == -1)
    {
        perror("Close server:");
        return false;
    }
    is_close = close(client_socket);
    if (is_close == -1)
    {
        perror("Close client:");
        return false;
    }

    return true;
}

bool TCPServer::AcceptHandler()
{
    int     num_fd{};
    ssize_t recv_buff_len{};
    ssize_t change_client{};
    json    receive_msg_to_parser{};

    while (true)
    {
        num_fd = epoll_wait(epoll_fd, polled_events, MAX_EVENTS, -1);
        for (int i = 0; i < num_fd; ++i)
        {
            if (polled_events[i].data.fd == server_socket)
            {
                client_socket = accept(server_socket, nullptr, nullptr);
                event.events  = EPOLLIN;
                event.data.fd = client_socket;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &event);
            }
            else
            {
                recv_buff_len =
                    recv(polled_events[i].data.fd, receive_buffer.data(), receive_buffer.size(), 0);

                if (recv_buff_len > 0)
                {
                    std::string msg_to_buffer{receive_buffer.data()};
                    receive_msg_to_parser = ParserHttPrequest(msg_to_buffer);
                    std::cout << std::setw(4) << receive_msg_to_parser << '\n';

                    change_client = write(polled_events[i].data.fd, http_response,
                                          strlen(http_response) * sizeof(char));
                    if (change_client == -1)
                    {
                        perror("error");
                    }
                }

                if (recv_buff_len < 1)
                {
                    close(polled_events[i].data.fd);
                }
            }
        }
    }

    return true;
}

bool TCPServer::RunAllThread()
{
    std::thread accept_thread(&TCPServer::AcceptHandler, this);
    accept_thread.join();
    return true;
}

} // namespace http