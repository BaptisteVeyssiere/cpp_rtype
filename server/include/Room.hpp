#pragma once

#include <chrono>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
#include "Request.hpp"

class Room
{
private:

	bool			start;
	bool			end;
	std::thread		thread;
	std::mutex		mutex;
	std::vector<unsigned int>	players;
	std::unordered_map<unsigned int, std::string>	playersName;
	std::queue<ServerRequest>	sendingQueue;
	std::queue<ClientRequest>	receivedQueue;

public:

	Room();
	~Room();

	void	addPlayer(unsigned int const &id);
	void	getRequestToSend(std::vector<ServerRequest> &requests);
	void	addReceivedRequest(ClientRequest const &requests);
	bool	isPlaying();
	bool	isFull();
	bool	playerExists(unsigned int const &id);

private:

	void	roomProcess();

};