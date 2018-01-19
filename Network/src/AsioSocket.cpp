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

}

void	AsioSocket::prepareToConnect()
{
	socket.open(boost::asio::ip::udp::v4());
	endpoint.address(boost::asio::ip::address::from_string(_address));
	endpoint.port(_port);
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
}

void	AsioSocket::sendRequest(std::vector<char> const &data, unsigned int const &id)
{
	if (id == 0)
	{
		socket.send_to(boost::asio::buffer(data.data(), data.size()), endpoint);
	}
	else
	{
		boost::asio::ip::udp::endpoint	endp;
		for (AsioClient client : clientList)
		{
			if (client._id == id)
				endp = client._endpoint;
		}
		socket.send_to(boost::asio::buffer(data.data(), data.size()), endp);
	}
}

void	AsioSocket::sendRequest(std::vector<char> const &data)
{
	socket.send_to(boost::asio::buffer(data.data(), data.size()), endpoint);
}

void	AsioSocket::receiveRequest(std::vector<char> &data, unsigned int &id)
{
	boost::asio::ip::udp::endpoint	sender;
	socket.receive_from(boost::asio::buffer(data.data(), data.size()), sender);
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

void	AsioSocket::receiveRequest(std::vector<char> &data)
{
	boost::asio::ip::udp::endpoint	sender;
	socket.receive_from(boost::asio::buffer(data.data(), data.size()), sender);
}

void	AsioSocket::registerAddress(std::string const &addr)
{
	_address = addr;
}

void	AsioSocket::registerPort(int const &port)
{
	_port = port;
}
