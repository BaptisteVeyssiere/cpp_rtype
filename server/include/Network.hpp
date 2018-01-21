#pragma once

#include <vector>
#include "AsioSocket.hpp"
#include "Request.hpp"

struct NetClient
{
	unsigned int _id;
	std::vector<char>	_received;
	std::vector<char>	_to_send;

	NetClient(unsigned int const &id) : _id(id) {

	}
};

class Network {

private:

	bool		started;
	AsioSocket	server;
	std::vector<NetClient>	clientList;

	Network();
	~Network();
	Network(Network const &cp) = delete;
	Network	&operator=(Network const &cp) = delete;

	void	receiveRequest();
	void	getRequests(std::vector<ClientRequest> &requests, NetClient &client);
	void	prepareClientsRequests(std::vector<ServerRequest> const &requests);

public:

	static Network &getInstance();

	bool	isStarted() const;

	void	startReceivingConnections(int const &port);
	
	void	getLastRequests(std::vector<ClientRequest>	&requests);

	void	sendRequestsTo(std::vector<ServerRequest> const &requests);

};