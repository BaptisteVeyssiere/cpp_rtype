#include <cstdlib>
#include <iostream>
#include <boost/asio/impl/src.hpp>
#include <boost/asio.hpp>
#include "Network.hpp"
#include "WinLibLoader.hpp"


enum { max_length = 1024 };

void server(boost::asio::io_context& io_context, unsigned short port)
{
	boost::asio::ip::udp::socket sock(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
	for (;;)
	{
		char data[max_length];
		boost::asio::ip::udp::endpoint sender_endpoint;
		size_t length = sock.receive_from(
			boost::asio::buffer(data, max_length), sender_endpoint);
		sock.send_to(boost::asio::buffer(data, length), sender_endpoint);
	}
}

int main(int argc, char **argv)
{
	WinLibLoader	libloader;
	std::vector<std::string>	v;

	try {
		v = libloader.readDirectory("monster");
		for (auto s : v)
		{
			std::cout << s << std::endl;
		}
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
	try
	{
		Network &net = Network::getInstance();
		/*if (argc != 2)
		{
			std::cerr << "Usage: blocking_udp_echo_server <port>\n";
			return 1;
		}*/

		//boost::asio::io_context io_context;

		//server(io_context, 45712);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return (0);
}