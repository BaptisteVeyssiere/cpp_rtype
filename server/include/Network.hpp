#pragma once

#include <vector>
#include "AsioSocket.hpp"
#include "Protocol.hpp"

struct NetClient
{
	unsigned int _id;
	std::vector<char>	_received;
	std::vector<char>	_to_send;

	NetClient(unsigned int const &id) : _id(id) {

	}
};

struct ClientRequest
{
	unsigned int					id;
	std::unique_ptr<Inputs>			input;
	std::unique_ptr<Connect>		connect;
};

struct ServerRequest
{
	unsigned int							id;
	std::unique_ptr<Header>					head;
	std::vector<std::unique_ptr<Entity>>	entities;
	std::vector<std::unique_ptr<Enemy>>		enemies;
	std::vector<std::unique_ptr<Player>>	players;
};

class Network {

private:

	AsioSocket	server;
	std::vector<NetClient>	clientList;

	Network();
	~Network();
	Network(Network const &cp) = delete;
	Network	&operator=(Network const &cp) = delete;

	void	receiveRequest();
	void	getRequests(std::vector<ClientRequest> &requests, NetClient &client);

public:

	static Network &getInstance();

	void	startReceivingConnections(int const &port);
	
	void	getLastRequests(std::vector<ClientRequest>	&requests);

	void	sendRequestsTo(std::vector<ServerRequest> const &requests);

};