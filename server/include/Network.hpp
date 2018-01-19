#pragma once

#include <vector>

class Network {

private:

	//ISocket	server;
	//std::vector<ISocket> clientList;

	Network();
	~Network();
	Network(Network const &cp) = delete;
	Network	&operator=(Network const &cp) = delete;

public:

	static Network &getInstance();
	


};