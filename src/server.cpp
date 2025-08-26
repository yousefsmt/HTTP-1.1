#include "server.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <nlohmann/json.hpp>

namespace http
{
using json = nlohmann::json;

TCPServer::TCPServer(const std::string& ip_address, const std::string& port_address) :
	ip_address_(ip_address), port_(port_address)
{
	CreateServerSocket();
}

TCPServer::~TCPServer()
{
	if(!CloseServerSocket())
	{
		std::cout << "ERROR: Sockets close failed.\n";
	}
}

bool TCPServer::CreateServerSocket()
{
	int is_correct{};
	uint16_t port_number_cast{};

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket == -1)
	{
		perror("Creation socket: ");
		return false;
	}

	port_number_cast = static_cast<uint16_t>(std::stoi(port_));

	server_address.sin_family = AF_INET;
	inet_pton(AF_INET, ip_address_.c_str(), &(server_address.sin_addr.s_addr));
	server_address.sin_port = htons(port_number_cast);
	server_length = sizeof(server_address);

	is_correct = bind(server_socket, reinterpret_cast<sockaddr*>(&server_address), server_length);
	if(is_correct == -1)
	{
		perror("Bind failed: ");
		return false;
	}

	is_correct = listen(server_socket, block_size);
	if(is_correct == -1)
	{
		perror("Listen failed: ");
		return false;
	}
	else
	{
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
	if(is_close == -1)
	{
		perror("Close server:");
		return false;
	}
	is_close = close(client_socket);
	if(is_close == -1)
	{
		perror("Close client:");
		return false;
	}

	return true;
}

bool TCPServer::AcceptHandler()
{
	sockaddr_in client_address{};
	socklen_t client_length{sizeof(client_address)};

	while(true)
	{
		client_socket =
			accept(server_socket, reinterpret_cast<sockaddr*>(&client_address), &client_length);
		if(client_socket == -1)
		{
			perror("accept failed: ");
			return false;
		}
		else
		{
			ReceiveHandler();
		}
	}

	return true;
}

bool TCPServer::ReceiveHandler()
{
	ssize_t is_correct{};

	is_correct = recv(client_socket, receive_buffer.data(), receive_buffer.size() - 1, 0);
	if(is_correct > 0 && receive_buffer[0] != '\0')
	{
		json parsed_msg;
		ParserMessage parse;
		std::string to_string_buffer = receive_buffer.data();
		std::cout << to_string_buffer;
		std::cout << "************************";
		parsed_msg = parse.ParserHttPrequest(to_string_buffer);
		std::cout << std::setw(4) << parsed_msg << '\n';
	}
	else if(is_correct == -1)
	{
		perror("recv failed: ");
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