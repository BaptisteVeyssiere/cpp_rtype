#include <iostream>
#include <algorithm>
#include <boost/asio/impl/src.hpp>
#include "AsioSocket.hpp"

AsioSocket::AsioSocket() : io_context(), socket(io_context), endpoint(), nextId(0)
{
	_id = 0;
	_address = "";
	_port = 0;
}

AsioSocket::AsioSocket(std::string const &addr, int const &port) : io_context(), socket(io_context), endpoint(), nextId(0)
{
	_id = 0;
	_address = addr;
	_port = port;
}

AsioSocket::~AsioSocket()
{
	if (socket.is_open())
		socket.close();
}

void	AsioSocket::prepareToConnect()
{
	socket.open(boost::asio::ip::udp::v4());
	endpoint.address(boost::asio::ip::address::from_string(_address));
	endpoint.port(_port);
	socket.non_blocking(true);
}

void	AsioSocket::getNewConnections(std::vector<unsigned int> &clients)
{
	for (AsioClient client : clientList)
	{
		if (std::find(clients.begin(), clients.end(), client._id) == clients.end())
			clients.push_back(client._id);
	}
}

void	AsioSocket::startReceivingConnections()
{
	socket.open(boost::asio::ip::udp::v4());
	socket.set_option(boost::asio::socket_base::reuse_address(true));
	socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), _port));
	socket.non_blocking(true);
}

void	AsioSocket::sendRequest(std::vector<char> &data, unsigned int const &id)
{
	try
	{
		std::size_t rsize = 0;
		if (id == 0)
		{
			rsize = socket.send_to(boost::asio::buffer(data), endpoint);
		}
		else
		{
			boost::asio::ip::udp::endpoint	endp;
			for (AsioClient client : clientList)
			{
				if (client._id == id)
					endp = client._endpoint;
			}
			rsize = socket.send_to(boost::asio::buffer(data), endp);
		}
		if (rsize > 0)
			data.erase(data.begin(), data.begin() + rsize);
	}
	catch (boost::system::system_error const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	AsioSocket::sendRequest(std::vector<char> &data)
{
	try
	{
		std::size_t rsize = socket.send_to(boost::asio::buffer(data), endpoint);
		if (rsize > 0)
			data.erase(data.begin(), data.begin() + rsize);
	}
	catch (boost::system::system_error const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	AsioSocket::receiveRequest(std::vector<char> &data, unsigned int &size, unsigned int &id)
{
	try
	{
		boost::asio::ip::udp::endpoint	sender;
		size = 0;
		id = 0;
		std::size_t len = socket.receive_from(boost::asio::buffer(data), sender);
		size = static_cast<unsigned int>(len);
		if (sender != endpoint)
		{
			bool isNew = true;
			for (AsioClient client : clientList)
			{
				if (client._endpoint == sender)
				{
					id = client._id;
					isNew = false;
					break;
				}
			}
			if (isNew)
			{
				clientList.push_back(AsioClient(sender, ++nextId));
				id = nextId;
			}
		}
	}
	catch (boost::system::system_error const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	AsioSocket::receiveRequest(std::vector<char> &data, unsigned int &size)
{
	try
	{
		boost::asio::ip::udp::endpoint	sender;
		size = 0;
		std::size_t len = socket.receive_from(boost::asio::buffer(data), sender);
		size = static_cast<unsigned int>(len);
	}
	catch (boost::system::system_error const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	AsioSocket::registerAddress(std::string const &addr)
{
	_address = addr;
}

void	AsioSocket::registerPort(int const &port)
{
	_port = port;
}
