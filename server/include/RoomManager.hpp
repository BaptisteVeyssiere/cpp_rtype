#pragma once

#include "Network.hpp"
#include "Room.hpp"

#define DEFAULTPORT 47591

class RoomManager
{
private:

	std::unordered_map<unsigned int, std::unique_ptr<Room>>	rooms;
	std::vector<unsigned int>			clients;

public:

	RoomManager();
	~RoomManager();

	void	process();

private:

	void	handleReceivedRequests();
	void	handleToSendRequests();

};