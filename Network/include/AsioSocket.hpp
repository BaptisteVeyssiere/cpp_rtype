#pragma once

#include <vector>
#include <boost/asio.hpp>
#include "ISocket.hpp"

struct AsioClient
{
	unsigned int	_id;
	boost::asio::ip::udp::endpoint	_endpoint;

	AsioClient(boost::asio::ip::udp::endpoint endpoint, unsigned int id = 0) : _endpoint(endpoint), _id(id)
	{
	}
};

class AsioSocket : public ISocket
{

private:

	boost::asio::io_context			io_context;
	boost::asio::ip::udp::socket	socket;
	boost::asio::ip::udp::endpoint	endpoint;
	unsigned int					nextId;
	std::vector<AsioClient>			clientList;

public:

	/**
	*	@brief Default constructor for AsioSocket
	*
	*	@param address is a string containing the distant server's address
	*	@param port is an int containing the port to use
	*	@return nothing
	*/
	AsioSocket();

	AsioSocket(std::string const &address, int const &port);

	/**
	*	@brief Default destructor for AsioSocket
	*
	*	@return nothing
	*/
	~AsioSocket();

	/**
	*	@brief client side function, prepare to connect to the server
	*
	*	@return void
	*/
	void	prepareToConnect();

	/**
	*	@brief server side function, add the new connections id to the container
	*
	*	@param clients is an unsigned int vector containing alreadry established connections
	*	@return void
	*/
	void	getNewConnections(std::vector<unsigned int> &clients);

	/**
	*	@brief server side function, used to open and bind the socket
	*
	*	@return void
	*/
	void	startReceivingConnections();

	/**
	*	@brief client side function to send a request
	*
	*	@param data is a char vector containing the request to send
	*	@return void
	*/
	void	sendRequest(std::vector<char> const &data);

	/**
	*	@brief server side function to send a request
	*
	*	@param data is a char vector containing the request to send
	*	@param id is an unsigned int containing the id of the distant client
	*	@return void
	*/
	void	sendRequest(std::vector<char> const &data, unsigned int const &id);

	/**
	*	@brief client side function to receive a request
	*
	*	@param data is a char vector which will contain the received request
	*	@return void
	*/
	void	receiveRequest(std::vector<char> &data);

	/**
	*	@brief server side function to send a request
	*
	*	@param data is a char vector containing the request to send
	*	@param id is an unsigned int which will contain the id of the client who sent data
	*	@return void
	*/
	void	receiveRequest(std::vector<char> &data, unsigned int &id);

	/**
	*	@brief register distant server address
	*
	*	@param addr is a string containing the address of the distant server
	*	@return void
	*/
	void	registerAddress(std::string const &addr);

	/**
	*	@brief register a port to use
	*
	*	@param port is an int containing the port to use
	*	@return void
	*/
	void	registerPort(int const &port);
};