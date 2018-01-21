#include <iostream>
#include <algorithm>
#include "Room.hpp"

Room::Room() : start(false), end(false), core(nullptr), thread(&Room::roomProcess, this)
{

}

Room::~Room()
{

}

void	Room::beforeTheGame()
{
	if (!receivedQueue.empty())
	{
		ClientRequest	request = receivedQueue.back();
		receivedQueue.pop();
		if (request.input != nullptr)
		{
			for (int i = 0; i < players.size(); ++i)
			{
				if (players[i] == request.id)
				{
					states[i].flip();
					break;
				}
			}
		}
	}
	if (std::find(states.begin(), states.end(), false) == states.end())
	{
		std::vector<std::string>	names;
		for (int i = 0; i < players.size(); ++i)
		{
			names.push_back(playersName[players[i]]);
		}
		core = std::make_unique<GameCore>(players.size(), names);
		start = true;
	}
}

void	Room::getGameCoreRequest()
{
	ServerRequest	request;
	//TODO getrequest
	for (int i = 0; i < players.size(); ++i)
	{
		ServerRequest tmp(request);
		tmp.id = players[i];
		sendingQueue.push(tmp);
	}
}

void	Room::roomProcess()
{
	while (true)
	{
		if (!start)
		{
			beforeTheGame();
		}
		else
		{
			getGameCoreRequest();
		}
		std::this_thread::yield();
	}
}

void	Room::addPlayer(unsigned int const &id)
{
	if (players.size() < 4)
	{
		players.push_back(id);
		states.push_back(false);
	}
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

