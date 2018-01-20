#include <iostream>

#ifdef _WIN32
#include <conio.h>
#endif

#include "AsioSocket.hpp"

int main(int argc, char **argv)
{
	try {
		AsioSocket server("", 4567);
		AsioSocket client(std::string("127.0.0.1"), 4567);
		server.startReceivingConnections();
		client.prepareToConnect();
		std::vector<char>	client_data;
		client_data.push_back('c');
		client_data.push_back('l');
		client_data.push_back('i');
		client_data.push_back('e');
		client_data.push_back('n');
		client_data.push_back('t');
		std::vector<char>	server_data;
		server_data.push_back('s');
		server_data.push_back('e');
		server_data.push_back('r');
		server_data.push_back('v');
		server_data.push_back('e');
		server_data.push_back('r');
		std::vector<char>	receive_data(1024, 0);
		std::cout << "Client send data: " << std::string(client_data.begin(), client_data.end()).c_str() << std::endl;
		client.sendRequest(client_data);
		unsigned int clientId = 0;
		unsigned int size = 0;
		std::cout << "server receive data" << std::endl;
		server.receiveRequest(receive_data, size, clientId);
		std::cout << "received[" << size << "]: " << std::string(receive_data.data()).c_str() << std::endl;
		std::cout << "server send data: " << std::string(server_data.begin(), server_data.end()).c_str() << std::endl;
		server.sendRequest(server_data, clientId);
		for (char val : receive_data)
		{
			val = 0;
		}
		std::cout << "Client receive data" << std::endl;
		client.receiveRequest(receive_data, size);
		std::cout << "received[" << size << "]: " << std::string(receive_data.data()).c_str() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
#ifdef _WIN32
	getch();
#endif
	return (0);
}