#include <iostream>
#include <algorithm>
#include "Room.hpp"

Room::Room() : start(false), end(false), thread(&Room::roomProcess, this)
{

}

Room::~Room()
{

}

void	Room::roomProcess()
{

}

void	Room::addPlayer(unsigned int const &id)
{
	if (players.size() < 4)
		players.push_back(id);
}

void	Room::getRequestToSend(std::vector<ServerRequest> &requests)
{
	mutex.lock();
	try
	{
		while (!sendingQueue.empty())
		{
			requests.push_back(sendingQueue.back());
			sendingQueue.pop();
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	mutex.unlock();
}

void	Room::addReceivedRequest(ClientRequest const &request)
{
	mutex.lock();
	try
	{
		if (request.connect != nullptr)
		{
			playersName[request.id] = std::string(request.connect->name);
		}
		else
		{
			receivedQueue.push(request);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	mutex.unlock();
}

bool	Room::isPlaying()
{
	return start;
}

bool	Room::isFull()
{
	return players.size() == 4;
}

bool	Room::playerExists(unsigned int const &id)
{
	return (std::find(players.begin(), players.end(), id) != players.end());
}

