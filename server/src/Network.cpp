#include <iostream>
#include "Network.hpp"

Network::Network()
{
}

Network::~Network()
{

}

Network	&Network::getInstance()
{
	static Network instance;
	return (instance);
}

void	Network::startReceivingConnections(int const &port)
{
	server.startReceivingConnections();
}

void	Network::receiveRequest()
{
	std::vector<char>	received(1024);
	unsigned int		size = 0;
	unsigned int		id = 0;
	server.receiveRequest(received, size, id);
	if (id != 0)
	{
		bool isNew = true;
		for (NetClient client : clientList)
		{
			if (client._id == id)
			{
				if (size > 0)
					client._received.insert(client._received.end(),
						received.begin(), received.begin() + size);
				isNew = false;
				break;
			}
		}
		if (isNew)
		{
			clientList.push_back(NetClient(id));
			if (size > 0)
				clientList.back()._received.insert(clientList.back()._received.begin(),
					received.begin(), received.begin() + size);
		}
	}
}

void	Network::getRequests(std::vector<ClientRequest> &requests, NetClient &client)
{
	while (client._received.size() >= sizeof(Inputs)
		|| client._received.size() >= sizeof(Connect))
	{
		uint16_t tmp;
		std::memcpy(&tmp, client._received.data(), sizeof(tmp));
		if (tmp == 1 && client._received.size() >= sizeof(Inputs))
		{
			std::unique_ptr<Inputs>	move(new Inputs());
			std::memcpy(move.get(), client._received.data(), sizeof(Inputs));
			client._received.erase(client._received.begin(), client._received.begin() + sizeof(Inputs));
			requests.push_back(ClientRequest());
			requests.back().id = client._id;
			requests.back().input.reset(move.get());
		}
		else if (tmp == 2 && client._received.size() >= sizeof(Connect))
		{
			std::unique_ptr<Connect>	connect(new Connect());
			std::memcpy(connect.get(), client._received.data(), sizeof(Connect));
			client._received.erase(client._received.begin(), client._received.begin() + sizeof(Connect));
			requests.push_back(ClientRequest());
			requests.back().id = client._id;
			requests.back().connect.reset(connect.get());
		}
		else
		{
			break;
		}
	}
}

void	Network::getLastRequests(std::vector<ClientRequest> &requests)
{
	try {
		receiveRequest();
		for (NetClient client : clientList)
		{
			if (client._received.size() >= sizeof(Inputs)
				|| client._received.size() >= sizeof(Connect))
			{
				getRequests(requests, client);
			}
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	Network::prepareClientsRequests(std::vector<ServerRequest> const &requests)
{
	for (int i = 0; i < requests.size(); ++i)
	{
		for (NetClient client : clientList)
		{
			if (requests[i].id == client._id)
			{
				if (requests[i].head != nullptr)
				{
					std::vector<char>	header = requests[i].head->getVector();
					client._to_send.insert(client._to_send.end(), header.begin(), header.end());
					for (int x = 0; x < requests[i].head->playersCount; ++x)
					{
						std::vector<char>	tmp = requests[i].players[x]->getVector();
						client._to_send.insert(client._to_send.end(), tmp.begin(), tmp.end());
					}
					for (int x = 0; x < requests[i].head->enemyCount; ++x)
					{
						std::vector<char>	tmp = requests[i].enemies[x]->getVector();
						client._to_send.insert(client._to_send.end(), tmp.begin(), tmp.end());
					}
					for (int x = 0; x < requests[i].head->entityCount; ++x)
					{
						std::vector<char>	tmp = requests[i].entities[x]->getVector();
						client._to_send.insert(client._to_send.end(), tmp.begin(), tmp.end());
					}
				}
				break;
			}
		}
	}
}

void	Network::sendRequestsTo(std::vector<ServerRequest> const &requests)
{
	try
	{
		prepareClientsRequests(requests);
		for (NetClient client : clientList)
		{
			if (client._to_send.size() > 0)
			{
				server.sendRequest(client._to_send, client._id);
			}
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

}