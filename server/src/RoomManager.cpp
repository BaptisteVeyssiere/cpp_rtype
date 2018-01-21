#include <algorithm>
#include "RoomManager.hpp"

RoomManager::RoomManager()
{
	Network	&net = Network::getInstance();
	if (!net.isStarted())
	{
		net.startReceivingConnections(DEFAULTPORT);
	}
}

RoomManager::~RoomManager()
{

}

void	RoomManager::handleReceivedRequests()
{
	std::vector<ClientRequest>	requests;
	Network::getInstance().getLastRequests(requests);
	for (int i = 0; i < requests.size(); ++i)
	{
		if (std::find(clients.begin(), clients.end(), requests[i].id) == clients.end())
		{
			clients.push_back(requests[i].id);
		}
		if (requests[i].connect != nullptr)
		{
			bool create = true;
			if (requests[i].connect->room > 0)
			{
				auto it = rooms.find(requests[i].connect->room);
				if (it != rooms.end())
				{
					if (!it->second->isFull() && !it->second->isPlaying())
					{
						it->second->addPlayer(requests[i].id);
						it->second->addReceivedRequest(requests[i]);
						create = false;
					}
				}
			}
			if (create == true)
			{
				for (auto it = rooms.begin(); it != rooms.end(); it++)
				{
					if (!it->second->isPlaying() && !it->second->isFull())
					{
						it->second->addPlayer(requests[i].id);
						it->second->addReceivedRequest(requests[i]);
						create = false;
						break;
					}
				}
				if (create == true)
				{
					unsigned int id = 0;
					while (rooms.find(++id) != rooms.end());
					rooms[id] = std::make_unique<Room>();
					rooms[id]->addPlayer(requests[i].id);
					rooms[id]->addReceivedRequest(requests[i]);
				}
			}
		}
		else if (requests[i].input != nullptr)
		{
			for (auto it = rooms.begin(); it != rooms.end(); it++)
			{
				if (it->second->playerExists(requests[i].id))
				{
					it->second->addReceivedRequest(requests[i]);
					break;
				}
			}
		}
	}
}

void	RoomManager::handleToSendRequests()
{
	std::vector<ServerRequest> requests;
	for (auto it = rooms.begin(); it != rooms.end(); it++)
	{
		it->second->getRequestToSend(requests);
	}
	if (!requests.empty())
		Network::getInstance().sendRequestsTo(requests);
}

void	RoomManager::process()
{
	while (true)
	{
		handleReceivedRequests();
		handleToSendRequests();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}