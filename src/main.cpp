#include <iostream>
#include <nlohmann/json.hpp>

#include "parser.hpp"
#include "server.hpp"

using json = nlohmann::json;
using namespace http;

int main(int argc, char* argv[])
{
	std::string ip_address = "0.0.0.0";
	std::string port_address = "80";

	switch(argc)
	{
		case 1:
			break;
		case 2:
			ip_address = argv[1];
			break;
		case 3:
			ip_address = argv[1];
			port_address = argv[2];
			break;
		default:
			std::cerr << "Usage: " << argv[0] << " [IP_ADDRESS] [PORT]\n";
			return 1;
	}

	try
	{
		TCPServer run_server(ip_address, port_address);
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Failed to start server: " << ex.what() << '\n';
		return 1;
	}

	return 0;
}
